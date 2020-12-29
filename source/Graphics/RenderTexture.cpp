#include "RenderTexture.h"
#include <memory>
#include <GL/glew.h>
#include <iostream>

struct RenderTextureImpl
{
	GLuint fbo;
	GLuint fboIntermediate;
	GLuint depthStencilRbo;
	bool initCalled;
	int width;
	int height;
	std::shared_ptr<Texture> renderedTexture;
	std::shared_ptr<Texture> renderedTextureMultisample;
	RenderTextureType textureType;
	bool enableAntiAliasing;

	RenderTextureImpl(int width, int height, RenderTextureType textureType, bool enableAntiAliasing) :
		initCalled(false),
		fbo(0),
		fboIntermediate(0),
		renderedTexture(nullptr),
		depthStencilRbo(0),
		width(width),
		height(height),
		textureType(textureType),
		enableAntiAliasing(enableAntiAliasing)
	{}

	bool initWithAA()
	{
		//creating frame buffer
		initCalled = true;
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		//creating multisample texture
		GLuint texColorBufferMultisample;
		glGenTextures(1, &texColorBufferMultisample);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texColorBufferMultisample);
		if (textureType == RenderTextureType::Float)
		{
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA16F, width, height, GL_TRUE);
		}
		else
		{
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA, width, height, GL_TRUE);
		}
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

		//setting texture to fbo
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, texColorBufferMultisample, 0);

		//creating multisampled rbo
		glGenRenderbuffers(1, &depthStencilRbo);
		glBindRenderbuffer(GL_RENDERBUFFER, depthStencilRbo);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		//setting rbo to fbo
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencilRbo);

		//creating texture class
		renderedTextureMultisample = std::make_shared<Texture>(texColorBufferMultisample, width, height, true);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "failed to initialize MSAA frame buffer" << std::endl;
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			return false;
		}

		//creating intermediate fbo
		glGenFramebuffers(1, &fboIntermediate);
		glBindFramebuffer(GL_FRAMEBUFFER, fboIntermediate);

		//creating texture
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

		//attach texture to framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

		//creating texture class for intermediate buffer texture
		renderedTexture = std::make_shared<Texture>(texColorBuffer, width, height, false);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "failed to initialize MSAA frame buffer (intermediate buffer)" << std::endl;
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			return false;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return true;
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
		glGenRenderbuffers(1, &depthStencilRbo);
		glBindRenderbuffer(GL_RENDERBUFFER, depthStencilRbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		//setting renderbuffer to framebuffer
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencilRbo);

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
	
	bool initDepth()
	{
		initCalled = true;
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		GLuint texDepth;
		glGenTextures(1, &texDepth);
		glBindTexture(GL_TEXTURE_2D, texDepth);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texDepth, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		renderedTexture = std::make_shared<Texture>(texDepth, width, height, false);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "failed to initialize depth framebuffer" << std::endl;
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
	
	if (data->textureType != RenderTextureType::IntegerDepth)
	{
		glDeleteRenderbuffers(1, &data->depthStencilRbo);
		if (data->enableAntiAliasing)
		{
			glDeleteFramebuffers(1, &data->fboIntermediate);
		}
	}
	glDeleteFramebuffers(1, &data->fbo);
	
}

bool RenderTexture::init()
{
	if (data->textureType == RenderTextureType::IntegerDepth)
	{
		return data->initDepth();
	}
	else
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
}

void RenderTexture::bind()
{
	if (!data->initCalled)
	{
		std::cout << "you should call init() before binding RenderTexture" << std::endl;
		return;
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, data->fbo);
	glViewport(0, 0, data->width, data->height);
}

int RenderTexture::getWidth()
{
	return data->width;
}

int RenderTexture::getHeight()
{
	return data->height;
}

void RenderTexture::updateTexture(bool preserveBinding)
{
	if (!data->initCalled)
	{
		std::cout << "trying to update texture without calling RenderTexture.init()" << std::endl;
		return;
	}

	if (data->textureType == RenderTextureType::IntegerDepth)
	{
		return;
	}

	if (data->enableAntiAliasing)
	{
		GLint prevDrawFbo = 0;
		GLint prevReadFbo = 0;
		if (preserveBinding)
		{
			glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &prevDrawFbo);
			glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &prevReadFbo);
		}

		glBindFramebuffer(GL_READ_FRAMEBUFFER, data->fbo);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, data->fboIntermediate);
		glBlitFramebuffer(0, 0, data->width, data->height, 0, 0, data->width, data->height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

		if (preserveBinding)
		{
			glBindFramebuffer(GL_READ_FRAMEBUFFER, prevReadFbo);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, prevDrawFbo);
		}
	}
}

Texture& RenderTexture::getRenderedTexture()
{
	if (!data->initCalled)
	{
		std::cout << "trying to get rendered texture without calling RenderTexture.init()" << std::endl;
	}

	return *data->renderedTexture;
}