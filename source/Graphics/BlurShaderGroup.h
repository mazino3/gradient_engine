#ifndef GRAPHICS_BLUR_SHADER_GROUP_H
#define GRAPHICS_BLUR_SHADER_GROUP_H

#include "BlurShader.h"
#include "RenderTexture.h"
#include <memory>

struct BlurShaderGroupImpl;

struct BlurShaderGroup
{
	BlurShaderGroup(float minRadius, float maxRadius, float step);
	void setRadius(float radius);
	void bind(Texture& screenTexture, float pixelSize, bool isHorizontal);

private:
	std::shared_ptr<BlurShaderGroupImpl> data;
};

#endif