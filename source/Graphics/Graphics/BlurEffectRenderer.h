#ifndef GRAPHICS_BLUR_EFFECT_RENDERER_H
#define GRAPHICS_BLUR_EFFECT_RENDERER_H

#include <Graphics/Shaders/BlurShader.h>
#include <Graphics/RenderTexture.h>
#include <memory>

struct BlurEffectRendererImpl;

struct BlurEffectRenderer
{
	BlurEffectRenderer(RenderTexture& additionalTexture);
	BlurEffectRenderer(RenderTexture& additionalTexture, float radius);

	void setNumberOfPasses(int passes);
	void render(RenderTexture& renderTarget);
private:
	std::shared_ptr<BlurEffectRendererImpl> data;
};

#endif