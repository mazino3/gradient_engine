#ifndef GRAPHICS_BLUR_EFFECT_RENDERER_H
#define GRAPHICS_BLUR_EFFECT_RENDERER_H

#include <Graphics/Shaders/BlurShader.h>
#include <Graphics/RenderTexture.h>
#include <memory>

struct BlurEffectRendererImpl;

struct BlurEffectRenderer
{
	BlurEffectRenderer();
	BlurEffectRenderer(float radius);

	void setNumberOfPasses(int passes);
	void render(RenderTexture& renderTarget, RenderTexture& additionalTexture);
private:
	std::shared_ptr<BlurEffectRendererImpl> data;
};

#endif