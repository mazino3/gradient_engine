#include "Renderer.h"
#include <vector>
#include <algorithm>

struct RendererImpl
{
	Camera camera;
	std::vector<std::shared_ptr<RenderObject>> renderObjects;
};

Renderer::Renderer()
{
	data = std::make_shared<RendererImpl>();
}

Camera& Renderer::getCamera()
{
	return data->camera;
}

void Renderer::renderScene()
{
	//todo: implement
}

RenderObject& Renderer::createRenderObject(Texture& texture, const GeometryDefinition& geometryDefinition, const Material& material)
{
	auto result = std::make_shared<RenderObject>(texture, geometryDefinition, material);
	data->renderObjects.push_back(result);
	return *result;
}

void Renderer::removeRenderObject(RenderObject& objectToRemove)
{
	std::remove_if(data->renderObjects.begin(), data->renderObjects.end(), [&](const auto& renderObject) 
	{
		return &(*renderObject) == &objectToRemove;
	});
}