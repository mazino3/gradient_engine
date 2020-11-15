#include "Texture.h"
#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

struct TextureImpl
{
	GLuint textureHandler;
	int width;
	int height;
};

Texture::Texture(const std::string& filename)
{
	_data = std::make_shared<TextureImpl>();
	
	glGenTextures(1, &_data->textureHandler);
	glBindTexture(GL_TEXTURE_2D, _data->textureHandler);
	
	int numComponents;
	unsigned char* imageData = stbi_load(filename.c_str(), &_data->width, &_data->height, &numComponents, 4);
	if (imageData == nullptr)
	{
		std::cout << "failed to load image with name: " << filename << std::endl;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _data->width, _data->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	

	stbi_image_free(imageData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &_data->textureHandler);
}

void Texture::bind()
{
	Texture::bind(0);
}

void Texture::bind(int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, _data->textureHandler);
}