#include "BloomEffectRenderer.h"
#include "BlurEffectRenderer.h"
#include "AddShader.h"
#include "FilterBrightShader.h"

struct BloomEffectRendererImpl
{
	RenderTexture& texture1;
	RenderTexture& texture2;
	BlurEffectRenderer blurEffectRenderer;
	AddShader addShader;
	FilterBrightShader filterBrightShader;
	Mesh screenMesh;
	int numberOfBlurPasses;
	float brightnessThreshold;

	BloomEffectRendererImpl(RenderTexture& texture1, RenderTexture& texture2);
};

BloomEffectRendererImpl::BloomEffectRendererImpl(RenderTexture& texture1, RenderTexture& texture2) :
	texture1(texture1),
	texture2(texture2),
	blurEffectRenderer(texture2, 24.0f),
	numberOfBlurPasses(3),
	brightnessThreshold(0.7f),
	screenMesh(GeometryDefinition::SCREEN)
{
}

BloomEffectRenderer::BloomEffectRenderer(RenderTexture& texture1, RenderTexture& texture2)
{
	data = std::make_shared<BloomEffectRendererImpl>(texture1, texture2);
}

void BloomEffectRenderer::setBrightnessThreshold(float threshold)
{
	data->brightnessThreshold = threshold;
}

void BloomEffectRenderer::setNumberOfBlurPasses(int numberOfPasses)
{
	data->numberOfBlurPasses = numberOfPasses;
}

void BloomEffectRenderer::render(RenderTexture& target)
{
	data->texture1.bind();
	data->filterBrightShader.bind();
	data->filterBrightShader.setScreenTexture(target.getRenderedTexture());
	data->filterBrightShader.setBrightnessThreshold(data->brightnessThreshold);
	data->screenMesh.draw();
	data->texture1.updateTexture(false);

	data->blurEffectRenderer.setNumberOfPasses(data->numberOfBlurPasses);
	data->blurEffectRenderer.render(data->texture1);

	data->texture2.bind();
	data->addShader.bind();
	data->addShader.setTexture1(target.getRenderedTexture());
	data->addShader.setTexture2(data->texture1.getRenderedTexture());
	data->screenMesh.draw();
	data->texture2.updateTexture(false);
}

RenderTexture& BloomEffectRenderer::getOutputTexture()
{
	return data->texture2;
}