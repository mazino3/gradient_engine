#ifndef GRAPHICS_RENDERER_H
#define GRAPHICS_RENDERER_H

#include <memory>
#include "Camera.h"
#include "RenderObject.h"
#include "Lights.h"

struct RendererImpl;

struct Renderer
{
	Renderer();

	Camera& getCamera();
	void renderScene();

	RenderObject& createRenderObject(Texture& texture, const GeometryDefinition& geometryDefinition, const Material& material);
	void removeRenderObject(RenderObject& renderObject);

	DirectionalLight& createDirectionalLight();
	void removeDirectionalLight(DirectionalLight& light);
	PositionalLight& createPositionalLight();
	void removePositionalLight(PositionalLight& light);

private:
	std::shared_ptr<RendererImpl> data;
};

#endif