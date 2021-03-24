#include <Graphics/BlurEffectRenderer.h>

struct BlurEffectRendererImpl
{
	BlurShader blurShader;
	Mesh screenMesh;
	RenderTexture& additionalTexture;
	int numberOfPasses;

	BlurEffectRendererImpl(RenderTexture& additionalTexture) :
		additionalTexture(additionalTexture),
		numberOfPasses(1),
		screenMesh(GeometryDefinition::SCREEN),
		blurShader(24.0f)
	{}

	BlurEffectRendererImpl(RenderTexture& additionalTexture, float radius) :
		additionalTexture(additionalTexture),
		numberOfPasses(1),
		screenMesh(GeometryDefinition::SCREEN),
		blurShader(radius)
	{}
};

BlurEffectRenderer::BlurEffectRenderer(RenderTexture& additionalTexture)
{
	data = std::make_shared<BlurEffectRendererImpl>(additionalTexture);
}

BlurEffectRenderer::BlurEffectRenderer(RenderTexture& additionalTexture, float radius)
{
	data = std::make_shared<BlurEffectRendererImpl>(additionalTexture, radius);
}

void BlurEffectRenderer::setNumberOfPasses(int passes)
{
	data->numberOfPasses = passes;
}

void BlurEffectRenderer::render(RenderTexture& renderTexture)
{
	data->blurShader.bind();
	data->blurShader.setPixelSize(1.0f / (float)renderTexture.getWidth());

	for (int i = 0; i < data->numberOfPasses * 2; i++)
	{
		auto& textureToBind = i % 2 == 0 ? data->additionalTexture : renderTexture;
		auto& textureUniform = i % 2 == 0 ? renderTexture : data->additionalTexture;

		textureToBind.bind();
		if (i <= 2)
		{
			textureToBind.setClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
			textureToBind.clear();
		}

		data->blurShader.setHorizontal(i % 2 == 0);
		data->blurShader.setScreenTexture(textureUniform.getRenderedTexture());
		data->screenMesh.draw();
		textureToBind.updateTexture(false);
	}
}