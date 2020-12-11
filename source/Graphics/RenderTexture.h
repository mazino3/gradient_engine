#ifndef GRAPHICS_RENDER_TEXTURE_H
#define GRAPHICS_RENDER_TEXTURE_H

#include "RenderTarget.h"
#include "Texture.h"
#include <memory>

struct RenderTextureImpl;

struct RenderTexture : RenderTarget
{
	RenderTexture(int width, int height);
	~RenderTexture();
	bool init();
	void bind();
	Texture& getRenderedTexture();
private:
	std::shared_ptr<RenderTextureImpl> data;
};

#endif