#include "ResizeComponent.h"

struct ResizeComponentImpl
{
	LevelObject& levelObject;
	Renderer& renderer;
	Resources& resources;

	std::weak_ptr<RenderObject> arrowMinusX;
	std::weak_ptr<RenderObject> arrowPlusX;
	std::weak_ptr<RenderObject> arrowMinusY;
	std::weak_ptr<RenderObject> arrowPlusY;
	std::weak_ptr<RenderObject> arrowMinusZ;
	std::weak_ptr<RenderObject> arrowPlusZ;

	bool isSelected;

	ResizeComponentImpl(LevelObject& levelObject, Renderer& renderer, Resources& resources) :
		levelObject(levelObject),
		renderer(renderer),
		resources(resources),
		isSelected(false)
	{}

	void updateArrowPositions();
};

ResizeComponent::ResizeComponent(LevelObject& levelObject, Renderer& renderer, Resources& resources)
{
	data = std::make_unique<ResizeComponentImpl>(levelObject, renderer, resources);
}

ResizeComponent::~ResizeComponent()
{
}

void ResizeComponent::onSelected()
{
	data->isSelected = true;
	auto arrowDef = GeometryDefinition::CUBE.scale(glm::vec3(0.1f, 0.1f, 0.1f));
	
	data->arrowMinusX = data->renderer.createRenderObject(*data->resources.getWhiteTexture().lock(), arrowDef, Material());
	data->arrowPlusX = data->renderer.createRenderObject(*data->resources.getWhiteTexture().lock(), arrowDef, Material());
	data->arrowMinusY = data->renderer.createRenderObject(*data->resources.getWhiteTexture().lock(), arrowDef, Material());
	data->arrowPlusY = data->renderer.createRenderObject(*data->resources.getWhiteTexture().lock(), arrowDef, Material());
	data->arrowMinusZ = data->renderer.createRenderObject(*data->resources.getWhiteTexture().lock(), arrowDef, Material());
	data->arrowPlusZ = data->renderer.createRenderObject(*data->resources.getWhiteTexture().lock(), arrowDef, Material());

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
}

void ResizeComponentImpl::updateArrowPositions()
{
	auto scale = levelObject.getScale();
	auto pos = levelObject.getPosition();

	arrowMinusX.lock()->transform.position = pos - glm::vec3(scale.x / 2 + 0.5f, 0, 0);
	arrowPlusX.lock()->transform.position = pos + glm::vec3(scale.x / 2 + 0.5f, 0, 0);

	arrowMinusY.lock()->transform.position = pos - glm::vec3(0, scale.y / 2 + 0.5f, 0);
	arrowPlusY.lock()->transform.position = pos + glm::vec3(0, scale.y / 2 + 0.5f, 0);

	arrowMinusZ.lock()->transform.position = pos - glm::vec3(0, 0, scale.z / 2 + 0.5f);
	arrowPlusZ.lock()->transform.position = pos + glm::vec3(0, 0, scale.z / 2 + 0.5f);
}

void ResizeComponent::update()
{
	if (!data->isSelected)
	{
		return;
	}
	data->updateArrowPositions();
}

