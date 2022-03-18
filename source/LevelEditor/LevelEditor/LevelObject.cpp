#include <LevelEditor/LevelObject.h>


struct LevelObjectImpl
{
	Renderer& renderer;
	std::weak_ptr<RenderObject> renderObject;

	LevelObjectImpl(Renderer& renderer);
};

LevelObjectImpl::LevelObjectImpl(Renderer& renderer) :
	renderer(renderer)
{}


LevelObject::LevelObject(Renderer& renderer, Resources& resources, glm::vec3 pos, glm::vec3 scale)
{
	data = std::make_unique<LevelObjectImpl>(renderer);
	data->renderObject = renderer.createRenderObject(*resources.getWhiteTexture().lock(), GeometryDefinition::CUBE, Material());
}

LevelObject::~LevelObject()
{
	data->renderer.removeRenderObject(*data->renderObject.lock());
}