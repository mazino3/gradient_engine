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
	int numberOfBlurPasses;
	float brightnessThreshold;

	BloomEffectRendererImpl(RenderTexture& texture1, RenderTexture& texture2);
};

BloomEffectRendererImpl::BloomEffectRendererImpl(RenderTexture& texture1, RenderTexture& texture2) :
	texture1(texture1),
	texture2(texture2),
	blurEffectRenderer(texture2),
	numberOfBlurPasses(3),
	brightnessThreshold(0.7f)
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

void BloomEffectRenderer::render(RenderTarget& target)
{
	//todo: implement
}

RenderTexture& BloomEffectRenderer::getOutputTexture()
{
	return data->texture1;
}