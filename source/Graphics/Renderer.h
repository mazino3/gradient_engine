#ifndef GRAPHICS_RENDERER_H
#define GRAPHICS_RENDERER_H

#include <memory>
#include "Camera.h"
#include "RenderObject.h"

struct RendererImpl;

struct Renderer
{
	Renderer();

	Camera& getCamera();
	void renderScene();
	RenderObject& createRenderObject(Texture& texture, const GeometryDefinition& geometryDefinition, const Material& material);
	void removeRenderObject(RenderObject& renderObject);

private:
	std::shared_ptr<RendererImpl> data;
};

#endif