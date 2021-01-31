#ifndef GRAPHICS_BLUR_EFFECT_RENDERER_H
#define GRAPHICS_BLUR_EFFECT_RENDERER_H

#include "BlurShader.h"
#include "RenderTexture.h"
#include <memory>

struct BlurEffectRendererImpl;

struct BlurEffectRenderer
{
	BlurEffectRenderer(RenderTexture& additionalTexture);
	void setNumberOfPasses(int passes);
	void render(RenderTexture& renderTarget);
private:
	std::shared_ptr<BlurEffectRendererImpl> data;
};

#endif