#include <Graphics/BlurEffectRenderer.h>

struct BlurEffectRendererImpl
{
	BlurShader blurShader;
	Mesh screenMesh;
	int numberOfPasses;

	BlurEffectRendererImpl() :
		numberOfPasses(1),
		screenMesh(GeometryDefinition::SCREEN),
		blurShader(24.0f)
	{}

	BlurEffectRendererImpl(float radius) :
		numberOfPasses(1),
		screenMesh(GeometryDefinition::SCREEN),
		blurShader(radius)
	{}
};

BlurEffectRenderer::BlurEffectRenderer()
{
	data = std::make_shared<BlurEffectRendererImpl>();
}

BlurEffectRenderer::BlurEffectRenderer(float radius)
{
	data = std::make_shared<BlurEffectRendererImpl>(radius);
}

void BlurEffectRenderer::setNumberOfPasses(int passes)
{
	data->numberOfPasses = passes;
}

void BlurEffectRenderer::render(RenderTexture& renderTexture, RenderTexture& additionalTexture)
{
	data->blurShader.bind();
	data->blurShader.setPixelSize(1.0f / (float)renderTexture.getWidth());

	for (int i = 0; i < data->numberOfPasses * 2; i++)
	{
		auto& textureToBind = i % 2 == 0 ? additionalTexture : renderTexture;
		auto& textureUniform = i % 2 == 0 ? renderTexture : additionalTexture;

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