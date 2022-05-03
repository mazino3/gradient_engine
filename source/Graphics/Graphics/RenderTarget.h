#ifndef GRAPHICS_RENDER_TARGET_H
#define GRAPHICS_RENDER_TARGET_H

#include <glm/vec4.hpp>
#include <memory>
#include <Graphics/Mesh.h>
#include <Graphics/Shaders/Shader.h>

struct RenderTargetImpl;

struct RenderTarget
{
	RenderTarget();
	virtual ~RenderTarget() {}
	virtual bool init() = 0;
	virtual void bind() = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	void setClearColor(const glm::vec4& color);
	void clear();
	void clearDepth();

private:

	std::shared_ptr<RenderTargetImpl> _data;
};

#endif