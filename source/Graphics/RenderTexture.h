#ifndef GRAPHICS_RENDER_TEXTURE_H
#define GRAPHICS_RENDER_TEXTURE_H

#include "RenderTarget.h"
#include <memory>

struct RenderTextureImpl;

struct RenderTexture : RenderTarget
{
	RenderTexture(int width, int height);
	~RenderTexture();
	bool init();
	void bind();
private:
	std::shared_ptr<RenderTextureImpl> data;
};

#endif