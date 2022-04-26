#ifndef RESIZE_COMPONENT_H
#define RESIZE_COMPONENT_H

#include <memory>
#include "LevelObject.h"

struct ResizeComponentImpl;

struct ResizeComponent
{
	ResizeComponent(LevelObject& levelObject, Renderer& renderer);
	~ResizeComponent();

	void onSelected();
	void onUnselected();

	void update();
private:
	std::unique_ptr<ResizeComponentImpl> data;
};

#endif