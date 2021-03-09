#ifndef GRAPHICS_BLUR_SHADER_GROUP_H
#define GRAPHICS_BLUR_SHADER_GROUP_H

#include "BlurShader.h"
#include <memory>

struct BlurShaderGroupImpl;

struct BlurShaderGroup
{
	BlurShaderGroup(float minRadius, float maxRadius, float step);
	void bind();
	void setRadius(float radius);

private:
	std::shared_ptr<BlurShaderGroupImpl> data;
};

#endif