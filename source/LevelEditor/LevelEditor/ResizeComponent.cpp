#include "ResizeComponent.h"

struct ResizeComponentImpl
{
	LevelObject& levelObject;
	Renderer& renderer;

	std::weak_ptr<RenderObject> arrowMinusX;
	std::weak_ptr<RenderObject> arrowPlusX;
	std::weak_ptr<RenderObject> arrowMinusY;
	std::weak_ptr<RenderObject> arrowPlusY;
	std::weak_ptr<RenderObject> arrowMinusZ;
	std::weak_ptr<RenderObject> arrowPlusZ;

	bool isSelected;

	ResizeComponentImpl(LevelObject& levelObject, Renderer& renderer) :
		levelObject(levelObject),
		renderer(renderer),
		isSelected(false)
	{}
};

ResizeComponent::ResizeComponent(LevelObject& levelObject, Renderer& renderer)
{
	data = std::make_unique<ResizeComponentImpl>(levelObject, renderer);
}

ResizeComponent::~ResizeComponent()
{
}

void ResizeComponent::onSelected()
{
	data->isSelected = true;
	auto arrowDef = GeometryDefinition::CUBE.scale(glm::vec3(0.1f, 0.1f, 0.1f));
	//todo: implement
}

void ResizeComponent::onUnselected()
{
	data->isSelected = false;
	//todo: implement
}

void ResizeComponent::update()
{
	if (!data->isSelected)
	{
		return;
	}
	//todo: implement
}

