#include <Graphics/BloomEffectRenderer.h>
#include <Graphics/BlurEffectRenderer.h>
#include <Graphics/Shaders/AddShader.h>
#include <Graphics/Shaders/FilterBrightShader.h>

struct BloomEffectRendererImpl
{
	RenderTexture* lastOutputTexture;

	BlurEffectRenderer blurEffectRenderer;
	AddShader addShader;

	FilterBrightShader filterBrightShader;
	Mesh screenMesh;
	int numberOfBlurPasses;
	float brightnessThreshold;

	BloomEffectRendererImpl();
};

BloomEffectRendererImpl::BloomEffectRendererImpl() :
	blurEffectRenderer(24.0f),
	numberOfBlurPasses(3),
	brightnessThreshold(0.7f),
	screenMesh(GeometryDefinition::SCREEN),
	lastOutputTexture(nullptr)
{
}

BloomEffectRenderer::BloomEffectRenderer()
{
	data = std::make_shared<BloomEffectRendererImpl>();
}

void BloomEffectRenderer::setBrightnessThreshold(float threshold)
{
	data->brightnessThreshold = threshold;
}

void BloomEffectRenderer::setNumberOfBlurPasses(int numberOfPasses)
{
	data->numberOfBlurPasses = numberOfPasses;
}

void BloomEffectRenderer::render(RenderTexture& target, RenderTexture& texture1, RenderTexture& texture2)
{
	texture1.bind();
	data->filterBrightShader.bind();
	data->filterBrightShader.setScreenTexture(target.getRenderedTexture());
	data->filterBrightShader.setBrightnessThreshold(data->brightnessThreshold);
	data->screenMesh.draw();
	texture1.updateTexture(false);

	data->blurEffectRenderer.setNumberOfPasses(data->numberOfBlurPasses);
	data->blurEffectRenderer.render(texture1, texture2);

	texture2.bind();
	data->addShader.bind();
	data->addShader.setTexture1(target.getRenderedTexture());
	data->addShader.setTexture2(texture1.getRenderedTexture());
	data->addShader.setMultiplier1(1.0f);
	data->addShader.setMultiplier2(1.0f);
	data->screenMesh.draw();
	texture2.updateTexture(false);
	data->lastOutputTexture = &texture2;
}

RenderTexture& BloomEffectRenderer::getOutputTexture()
{
	return *data->lastOutputTexture;
}