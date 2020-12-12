#ifndef GRAPHICS_RENDER_TEXTURE_H
#define GRAPHICS_RENDER_TEXTURE_H

#include "RenderTarget.h"
#include "Texture.h"
#include <memory>

struct RenderTextureImpl;

enum class RenderTextureType
{
	Integer,
	Float
};

struct RenderTexture : RenderTarget
{
	RenderTexture(int width, int height, RenderTextureType textureType);
	~RenderTexture();
	bool init() override;
	void bind() override;
	int getWidth() override;
	int getHeight() override;
	Texture& getRenderedTexture();
private:
	std::shared_ptr<RenderTextureImpl> data;
};

#endif