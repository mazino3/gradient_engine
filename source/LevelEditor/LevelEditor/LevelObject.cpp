#include <LevelEditor/LevelObject.h>
#include <LevelEditor/ResizeComponent.h>
#include <LevelEditor/DependencyKeys.h>
#include <iostream>

using namespace DependencyKeys;

struct LevelObjectImpl
{
	Renderer& renderer;
	SelectionManager& selectionManager;
	RaycastManager& raycastManager;
	RaycastManager& hoverRaycastManager;
	Resources& resources;

	std::weak_ptr<RenderObject> renderObject;
	std::shared_ptr<SelectionSubscription> selectionSubscription;
	AABB aabb;
	int selectionId;
	ResizeComponent resizeComponent;

	LevelObjectImpl(DepSupplier& depSupplier, LevelObject& levelObject);

	bool isSelected;
	void onSelectionUpdated(bool isSelected);
};

LevelObjectImpl::LevelObjectImpl(DepSupplier& depSupplier, LevelObject& levelObject) :
	renderer(depSupplier.get<Renderer>()),
	selectionManager(depSupplier.get<SelectionManager>()),
	raycastManager(depSupplier.get(RAYCAST_MANAGER)),
	hoverRaycastManager(depSupplier.get(HOVER_RAYCAST_MANAGER)),
	resources(depSupplier.get<Resources>()),
	isSelected(false),
	resizeComponent(levelObject, depSupplier)
{}


LevelObject::LevelObject(DepSupplier& depSupplier, glm::vec3 pos, glm::vec3 scale)
{
	data = std::make_unique<LevelObjectImpl>(depSupplier, *this);
	data->renderObject = data->renderer.createRenderObject(*data->resources.getWhiteTexture().lock(), GeometryDefinition::CUBE, Material());
	data->aabb.position = pos;
	data->aabb.size = scale;
	data->renderObject.lock()->transform.position = pos;
	data->renderObject.lock()->transform.scale = scale;
	data->selectionId = data->selectionManager.getId();

	data->raycastManager.registerAABB(data->aabb, [this]() 
	{
			std::cout << "raycast hit!" << std::endl;
			data->selectionManager.fireSelectionChanged(data->selectionId);
	});

	data->hoverRaycastManager.registerAABB(data->aabb, [this]() 
	{
			if (!data->isSelected)
			{
				data->renderObject.lock()->hasOutline = true;
			}
	});

	data->selectionSubscription = data->selectionManager.subscribe([this](int selectedId, int prevId) 
	{
			data->onSelectionUpdated(selectedId == data->selectionId);
	});

	data->resizeComponent.onArrowClicked([](ArrowType arrowType) 
	{
			std::cout << "arrow clicked: " << (int)arrowType << std::endl;
	});
}

void LevelObjectImpl::onSelectionUpdated(bool isSelected)
{
	if (this->isSelected == isSelected)
	{
		return;
	}
	this->isSelected = isSelected;

	if (isSelected)
	{
		resizeComponent.onSelected();
	}
	else
	{
		resizeComponent.onUnselected();
	}

	renderObject.lock()->hasOutline = isSelected && false;
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
	data->resizeComponent.update();
}

LevelDataObject LevelObject::toDataObject()
{
	return LevelDataObject(data->aabb.position, data->aabb.size);
}