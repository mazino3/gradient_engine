#ifndef GRAPHICS_TEXTURE_H
#define GRAPHICS_TEXTURE_H

#include <string>
#include <memory>

struct TextureImpl;

struct Texture
{
	Texture(unsigned int handler, int width, int height); //wrap existing texture
	Texture(const std::string& filename);
	~Texture();
	void bind(int unit);
	void bind();
private:
	std::shared_ptr<TextureImpl> _data;
};

#endif