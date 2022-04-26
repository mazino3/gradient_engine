#include <LevelEditor/LevelObject.h>
#include <iostream>

struct LevelObjectImpl
{
	Renderer& renderer;
	SelectionManager& selectionManager;
	RaycastManager& raycastManager;
	RaycastManager& hoverRaycastManager;

	std::weak_ptr<RenderObject> renderObject;
	std::shared_ptr<SelectionSubscription> selectionSubscription;
	AABB aabb;
	int selectionId;

	LevelObjectImpl(Renderer& renderer, SelectionManager& selectionManager, RaycastManager& raycastManager, RaycastManager& hoverRaycastManager);

	bool isSelected;
	void onSelectionUpdated(bool isSelected);
};

LevelObjectImpl::LevelObjectImpl(Renderer& renderer, SelectionManager& selectionManager, RaycastManager& raycastManager, RaycastManager& hoverRaycastManager) :
	renderer(renderer),
	selectionManager(selectionManager),
	raycastManager(raycastManager),
	hoverRaycastManager(hoverRaycastManager),
	isSelected(false)
{}


LevelObject::LevelObject(Renderer& renderer, 
					    Resources& resources, 
						SelectionManager& selectionManager, 
						RaycastManager& raycastManager,
						RaycastManager& hoverRaycastManager,
						glm::vec3 pos, 
						glm::vec3 scale)
{
	data = std::make_unique<LevelObjectImpl>(renderer, selectionManager, raycastManager, hoverRaycastManager);
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

	hoverRaycastManager.registerAABB(data->aabb, [this]() 
	{
			data->renderObject.lock()->hasOutline = true;
	});

	data->selectionSubscription = selectionManager.subscribe([this](int selectedId, int prevId) 
	{
			data->onSelectionUpdated(selectedId == data->selectionId);
	});
}

void LevelObjectImpl::onSelectionUpdated(bool isSelected)
{
	if (this->isSelected == isSelected)
	{
		return;
	}
	this->isSelected = isSelected;

	renderObject.lock()->hasOutline = isSelected;
}

LevelObject::~LevelObject()
{
	data->renderer.removeRenderObject(*data->renderObject.lock());
	data->raycastManager.unregisterAABB(data->aabb);
	data->hoverRaycastManager.unregisterAABB(data->aabb);
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