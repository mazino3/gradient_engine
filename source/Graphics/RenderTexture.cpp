#include "RenderTexture.h"

#include <GL/glew.h>
#include <iostream>

struct RenderTextureImpl
{
	GLuint fbo;
	GLuint texColorBuffer;
	GLuint depthStencilRenderbuffer;
	bool initCalled;
	int width;
	int height;

	RenderTextureImpl(int width, int height) :
		initCalled(false),
		fbo(0),
		texColorBuffer(0),
		depthStencilRenderbuffer(0),
		width(width),
		height(height)
	{}
};

RenderTexture::RenderTexture(int width, int height)
{
	data = std::make_shared<RenderTextureImpl>(width, height);
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
	//creating frame buffer
	data->initCalled = true;
	glGenFramebuffers(1, &data->fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, data->fbo);

	//creating texture to render into
	glGenTextures(1, &data->texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, data->texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data->width, data->height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	//setting this texture to framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, data->texColorBuffer, 0);

	//creating render buffer for depth and stencil
	glGenRenderbuffers(1, &data->depthStencilRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, data->depthStencilRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, data->width, data->height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	//setting renderbuffer to framebuffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, data->depthStencilRenderbuffer);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "failed to initialize frame buffer" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
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