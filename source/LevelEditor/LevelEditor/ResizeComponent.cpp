#include "ResizeComponent.h"
#include "DependencyKeys.h"
#include <functional>

using namespace DependencyKeys;

struct ResizeComponentImpl
{
	LevelObject& levelObject;
	Renderer& renderer;
	Resources& resources;
	RaycastManager& arrowRaycastManager;

	std::function<void(ArrowType)> arrowClickCallback;

	std::weak_ptr<RenderObject> arrowMinusX;
	std::weak_ptr<RenderObject> arrowPlusX;
	std::weak_ptr<RenderObject> arrowMinusY;
	std::weak_ptr<RenderObject> arrowPlusY;
	std::weak_ptr<RenderObject> arrowMinusZ;
	std::weak_ptr<RenderObject> arrowPlusZ;

	std::shared_ptr<AABB> aabbMinusX;
	std::shared_ptr<AABB> aabbPlusX;
	std::shared_ptr<AABB> aabbMinusY;
	std::shared_ptr<AABB> aabbPlusY;
	std::shared_ptr<AABB> aabbMinusZ;
	std::shared_ptr<AABB> aabbPlusZ;

	bool isSelected;

	ResizeComponentImpl(LevelObject& levelObject, DepSupplier& depSupplier) :
		levelObject(levelObject),
		renderer(depSupplier.get<Renderer>()),
		resources(depSupplier.get<Resources>()),
		arrowRaycastManager(depSupplier.get(ARROW_RAYCAST_MANAGER)),
		isSelected(false),
		arrowClickCallback([](ArrowType arrowType) {})
	{}

	void updateArrowPositions();

	std::function<void(void)> getRaycastCallback(ArrowType arrowType);
};

std::function<void(void)> ResizeComponentImpl::getRaycastCallback(ArrowType arrowType)
{
	return [arrowType, this]() 
	{
		arrowClickCallback(arrowType);
	};
}

ResizeComponent::ResizeComponent(LevelObject& levelObject, DepSupplier& depSupplier)
{
	data = std::make_unique<ResizeComponentImpl>(levelObject, depSupplier);
}

ResizeComponent::~ResizeComponent()
{
}

void ResizeComponent::onArrowClicked(std::function<void(ArrowType)> callback)
{
	data->arrowClickCallback = callback;
}

void ResizeComponent::onSelected()
{
	data->isSelected = true;
	auto arrowDef = GeometryDefinition::createArrow(20, 1.0f, 0.3f, 0.5f, 0.8f).scale(glm::vec3(0.5f, 0.5f, 0.8f));
	
	glm::vec3 xColor(1.0f, 0.0f, 0.0f);
	glm::vec3 yColor(0.0f, 1.0f, 0.0f);
	glm::vec3 zColor(0.0f, 0.0f, 1.0f);

	Material xArrowMat;
	Material yArrowMat;
	Material zArrowMat;

	xArrowMat.specular = glm::vec3(0, 0, 0);
	yArrowMat.specular = glm::vec3(0, 0, 0);
	zArrowMat.specular = glm::vec3(0, 0, 0);

	xArrowMat.diffuse = xColor;
	yArrowMat.diffuse = yColor;
	zArrowMat.diffuse = zColor;
	
	xArrowMat.ambient = xColor;
	yArrowMat.ambient = yColor;
	zArrowMat.ambient = zColor;

	data->arrowMinusX = data->renderer.createRenderObject(*data->resources.getWhiteTexture().lock(), arrowDef.rotate(glm::vec3(0, -90, 0)), xArrowMat);
	data->arrowPlusX = data->renderer.createRenderObject(*data->resources.getWhiteTexture().lock(), arrowDef.rotate(glm::vec3(0, 90, 0)), xArrowMat);
	data->arrowMinusY = data->renderer.createRenderObject(*data->resources.getWhiteTexture().lock(), arrowDef.rotate(glm::vec3(90, 0, 0)), yArrowMat);
	data->arrowPlusY = data->renderer.createRenderObject(*data->resources.getWhiteTexture().lock(), arrowDef.rotate(glm::vec3(-90, 0, 0)), yArrowMat);
	data->arrowMinusZ = data->renderer.createRenderObject(*data->resources.getWhiteTexture().lock(), arrowDef.rotate(glm::vec3(180, 0, 0)), zArrowMat);
	data->arrowPlusZ = data->renderer.createRenderObject(*data->resources.getWhiteTexture().lock(), arrowDef, zArrowMat);

	data->aabbMinusX = std::make_shared<AABB>(glm::vec3(0, 0, 0), glm::vec3(0.2f, 0.2f, 0.2f));
	data->aabbPlusX = std::make_shared<AABB>(glm::vec3(0, 0, 0), glm::vec3(0.2f, 0.2f, 0.2f));
	data->aabbMinusY = std::make_shared<AABB>(glm::vec3(0, 0, 0), glm::vec3(0.2f, 0.2f, 0.2f));
	data->aabbPlusY = std::make_shared<AABB>(glm::vec3(0, 0, 0), glm::vec3(0.2f, 0.2f, 0.2f));
	data->aabbMinusZ = std::make_shared<AABB>(glm::vec3(0, 0, 0), glm::vec3(0.2f, 0.2f, 0.2f));
	data->aabbPlusZ = std::make_shared<AABB>(glm::vec3(0, 0, 0), glm::vec3(0.2f, 0.2f, 0.2f));

	data->arrowRaycastManager.registerAABB(*data->aabbMinusX, data->getRaycastCallback(ArrowType::MINUS_X));
	data->arrowRaycastManager.registerAABB(*data->aabbPlusX, data->getRaycastCallback(ArrowType::PLUS_X));
	data->arrowRaycastManager.registerAABB(*data->aabbMinusY, data->getRaycastCallback(ArrowType::MINUS_Y));
	data->arrowRaycastManager.registerAABB(*data->aabbPlusY, data->getRaycastCallback(ArrowType::PLUS_Y));
	data->arrowRaycastManager.registerAABB(*data->aabbMinusZ, data->getRaycastCallback(ArrowType::MINUS_Z));
	data->arrowRaycastManager.registerAABB(*data->aabbPlusZ, data->getRaycastCallback(ArrowType::PLUS_Z));

	data->arrowMinusX.lock()->renderLayer = 1;
	data->arrowPlusX.lock()->renderLayer = 1;
	data->arrowMinusY.lock()->renderLayer = 1;
	data->arrowPlusY.lock()->renderLayer = 1;
	data->arrowMinusZ.lock()->renderLayer = 1;
	data->arrowPlusZ.lock()->renderLayer = 1;

	data->updateArrowPositions();
}

void ResizeComponent::onUnselected()
{
	data->isSelected = false;
	
	data->renderer.removeRenderObject(*data->arrowMinusX.lock());
	data->renderer.removeRenderObject(*data->arrowPlusX.lock());
	data->renderer.removeRenderObject(*data->arrowMinusY.lock());
	data->renderer.removeRenderObject(*data->arrowPlusY.lock());
	data->renderer.removeRenderObject(*data->arrowMinusZ.lock());
	data->renderer.removeRenderObject(*data->arrowPlusZ.lock());

	data->arrowRaycastManager.unregisterAABB(*data->aabbMinusX);
	data->arrowRaycastManager.unregisterAABB(*data->aabbPlusX);
	data->arrowRaycastManager.unregisterAABB(*data->aabbMinusY);
	data->arrowRaycastManager.unregisterAABB(*data->aabbPlusY);
	data->arrowRaycastManager.unregisterAABB(*data->aabbMinusZ);
	data->arrowRaycastManager.unregisterAABB(*data->aabbPlusZ);
}

void ResizeComponentImpl::updateArrowPositions()
{
	auto scale = levelObject.getScale();
	auto pos = levelObject.getPosition();

	auto posMinusX = pos - glm::vec3(scale.x / 2 + 0.5f, 0, 0);
	auto posPlusX = pos + glm::vec3(scale.x / 2 + 0.5f, 0, 0);
	auto posMinusY = pos - glm::vec3(0, scale.y / 2 + 0.5f, 0);
	auto posPlusY = pos + glm::vec3(0, scale.y / 2 + 0.5f, 0);
	auto posMinusZ = pos - glm::vec3(0, 0, scale.z / 2 + 0.5f);
	auto posPlusZ = pos + glm::vec3(0, 0, scale.z / 2 + 0.5f);

	arrowMinusX.lock()->transform.position = posMinusX;
	arrowPlusX.lock()->transform.position = posPlusX;
	arrowMinusY.lock()->transform.position = posMinusY;
	arrowPlusY.lock()->transform.position = posPlusY;
	arrowMinusZ.lock()->transform.position = posMinusZ;
	arrowPlusZ.lock()->transform.position = posPlusZ;

	aabbMinusX->position = posMinusX;
	aabbPlusX->position = posPlusX;
	aabbMinusY->position = posMinusY;
	aabbPlusY->position = posPlusY;
	aabbMinusZ->position = posMinusZ;
	aabbPlusZ->position = posPlusZ;
}

void ResizeComponent::update()
{
	if (!data->isSelected)
	{
		return;
	}
	data->updateArrowPositions();
}

