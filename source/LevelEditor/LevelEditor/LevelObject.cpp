#include <LevelEditor/LevelObject.h>
#include <iostream>

struct LevelObjectImpl
{
	Renderer& renderer;
	SelectionManager& selectionManager;
	RaycastManager& raycastManager;

	std::weak_ptr<RenderObject> renderObject;
	std::shared_ptr<SelectionSubscription> selectionSubscription;
	AABB aabb;
	int selectionId;

	LevelObjectImpl(Renderer& renderer, SelectionManager& selectionManager, RaycastManager& raycastManager);
};

LevelObjectImpl::LevelObjectImpl(Renderer& renderer, SelectionManager& selectionManager, RaycastManager& raycastManager) :
	renderer(renderer),
	selectionManager(selectionManager),
	raycastManager(raycastManager)
{}


LevelObject::LevelObject(Renderer& renderer, Resources& resources, SelectionManager& selectionManager, 
						RaycastManager& raycastManager, glm::vec3 pos, glm::vec3 scale)
{
	data = std::make_unique<LevelObjectImpl>(renderer, selectionManager, raycastManager);
	data->renderObject = renderer.createRenderObject(*resources.getWhiteTexture().lock(), GeometryDefinition::CUBE, Material());
	data->aabb.position = pos;
	data->aabb.size = scale;
	data->renderObject.lock()->transform.position = pos;
	data->renderObject.lock()->transform.scale = scale;
	data->selectionId = data->selectionManager.getId();

	raycastManager.registerAABB(data->aabb, [this]() 
	{
			std::cout << "raycast hit!" << std::endl;
			data->selectionManager.fireSelectionChanged(data->selectionId);
	});

	data->selectionSubscription = selectionManager.subscribe([this](int selectedId, int prevId) 
	{
			if (selectedId == data->selectionId)
			{
				std::cout << "selected!" << std::endl;
			}
			data->renderObject.lock()->hasOutline = (selectedId == data->selectionId);
	});
}

LevelObject::~LevelObject()
{
	data->renderer.removeRenderObject(*data->renderObject.lock());

}

void LevelObject::setPosition(const glm::vec3& pos)
{
	data->aabb.position = pos;
	data->renderObject.lock()->transform.position = pos;
}

glm::vec3 LevelObject::getPosition()
{
	return data->aabb.position;
}

AABB& LevelObject::getAABB()
{
	return data->aabb;
}

glm::vec3 LevelObject::getScale()
{
	return data->aabb.size;
}

void LevelObject::setScale(const glm::vec3& scale)
{
	data->aabb.size = scale;
	data->renderObject.lock()->transform.scale = scale;
}

void LevelObject::setOutlineEnabled(bool enabled)
{
	data->renderObject.lock()->hasOutline = enabled;
}

bool LevelObject::getOutlineEnabled()
{
	return data->renderObject.lock()->hasOutline;
}

void LevelObject::update()
{
}

LevelDataObject LevelObject::toDataObject()
{
	return LevelDataObject(data->aabb.position, data->aabb.size);
}