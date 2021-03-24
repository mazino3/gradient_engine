#include <GL/glew.h>
#include <Graphics/RenderTarget.h>

struct RenderTargetImpl
{
	glm::vec4 color;
};

RenderTarget::RenderTarget()
{
	_data = std::make_shared<RenderTargetImpl>();
}

void RenderTarget::setClearColor(const glm::vec4& color)
{
	_data->color = color;
}

void RenderTarget::clear()
{
	glClearColor(_data->color.r, _data->color.g, _data->color.b, _data->color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}