#include "RenderTexture.h"
#include <memory>
#include <GL/glew.h>
#include <iostream>

struct RenderTextureImpl
{
	GLuint fbo;
	GLuint depthStencilRenderbuffer;
	bool initCalled;
	int width;
	int height;
	std::shared_ptr<Texture> renderedTexture;
	RenderTextureType textureType;
	bool enableAntiAliasing;

	RenderTextureImpl(int width, int height, RenderTextureType textureType, bool enableAntiAliasing) :
		initCalled(false),
		fbo(0),
		renderedTexture(nullptr),
		depthStencilRenderbuffer(0),
		width(width),
		height(height),
		textureType(textureType),
		enableAntiAliasing(enableAntiAliasing)
	{}

	bool initWithAA()
	{
		return false;
	}

	bool initWithoutAA()
	{
		//creating frame buffer
		initCalled = true;
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		//creating texture to render into
		GLuint texColorBuffer;
		glGenTextures(1, &texColorBuffer);
		glBindTexture(GL_TEXTURE_2D, texColorBuffer);
		if (textureType == RenderTextureType::Float)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		//setting this texture to framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

		//creating render buffer for depth and stencil
		glGenRenderbuffers(1, &depthStencilRenderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthStencilRenderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		//setting renderbuffer to framebuffer
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencilRenderbuffer);

		//creating texture class
		renderedTexture = std::make_shared<Texture>(texColorBuffer, width, height, false);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "failed to initialize frame buffer (no AA)" << std::endl;
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			return false;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return true;
	}
};

RenderTexture::RenderTexture(int width, int height, RenderTextureType textureType ,bool enableAntiAliasing)
{
	data = std::make_shared<RenderTextureImpl>(width, height, textureType, enableAntiAliasing);
}

RenderTexture::~RenderTexture()
{
	if (!data->initCalled)
	{
		return;
	}
	//todo: implement
}

bool RenderTexture::init()
{
	if (data->enableAntiAliasing)
	{
		return data->initWithAA();
	}
	else
	{
		return data->initWithoutAA();
	}
}

void RenderTexture::bind()
{
	if (!data->initCalled)
	{
		std::cout << "you should call init() before binding RenderTexture" << std::endl;
		return;
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, data->fbo);
}

int RenderTexture::getWidth()
{
	return data->width;
}

int RenderTexture::getHeight()
{
	return data->height;
}

Texture& RenderTexture::getRenderedTexture()
{
	if (!data->initCalled)
	{
		std::cout << "trying to get rendered texture without calling RenderTexture.init()" << std::endl;
	}

	return *data->renderedTexture;
}