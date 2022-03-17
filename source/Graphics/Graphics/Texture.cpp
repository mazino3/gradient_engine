#include <Graphics/Texture.h>
#include <GL/glew.h>
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

struct TextureImpl
{
	GLuint textureHandler;
	int width;
	int height;
	bool multisample;
};



Texture::Texture(unsigned int handler, int width, int height, bool multisample)
{
	_data = std::make_shared<TextureImpl>();
	_data->textureHandler = handler;
	_data->width = width;
	_data->height = height;
	_data->multisample = multisample;
}

Texture Texture::createWhiteTexture()
{
	unsigned int handler;
	glGenTextures(1, &handler);
	glBindTexture(GL_TEXTURE_2D, handler);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	unsigned char imageData[] = { 0xFF, 0xFF, 0xFF, 0xFF };

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	return Texture(handler, 1, 1, false);
}

Texture::Texture(const std::string& filename)
{
	_data = std::make_shared<TextureImpl>();
	_data->multisample = false;
	
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
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _data->width, _data->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glHint(GL_GENERATE_MIPMAP_HINT, GL_FASTEST);
	glGenerateMipmap(GL_TEXTURE_2D);

	if (glewIsSupported("GL_EXT_texture_filter_anisotropic"))
	{
		GLfloat anisoSetting = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoSetting);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);
	}

	stbi_image_free(imageData);
}

Texture::Texture(Texture&& other)
{
	_data = other._data;
	other._data = std::shared_ptr<TextureImpl>(nullptr);
}

Texture::~Texture()
{
	if (!_data)
	{
		return;
	}
	glDeleteTextures(1, &_data->textureHandler);
}

void Texture::bind()
{
	Texture::bind(0);
}

void Texture::bind(int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	if (_data->multisample)
	{
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _data->textureHandler);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, _data->textureHandler);
	}
}