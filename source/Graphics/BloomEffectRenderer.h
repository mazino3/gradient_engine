#ifndef GRAPHICS_BLOOM_EFFECT_RENDERER_H
#define GRAPHICS_BLOOM_EFFECT_RENDERER_H

#include <memory>
#include "RenderTexture.h"

struct BloomEffectRendererImpl;

struct BloomEffectRenderer
{
	BloomEffectRenderer(RenderTexture& additionalTexture1, RenderTexture& additionalTexture2);
	void render(RenderTarget& target);
	void setNumberOfBlurPasses(int numberOfPasses);
	void setBrightnessThreshold(float threshold);
	RenderTexture& getOutputTexture();
private:
	std::shared_ptr<BloomEffectRendererImpl> data;
};

#endif