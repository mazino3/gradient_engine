#ifndef RESIZE_COMPONENT_H
#define RESIZE_COMPONENT_H

#include <memory>
#include <functional>
#include "LevelObject.h"
#include "Resources.h"
#include "DependencyKeys.h"
#include "DepSupplier.h"


enum class ArrowType
{
	MINUS_X,
	MINUS_Y,
	MINUS_Z,
	PLUS_X,
	PLUS_Y,
	PLUS_Z
};

struct ResizeComponentImpl;

struct ResizeComponent
{
	ResizeComponent(LevelObject& levelObject, DepSupplier& depSupplier);
	~ResizeComponent();

	void onSelected();
	void onUnselected();
	void update();
	void onArrowClicked(std::function<void(ArrowType)> callback);

private:
	std::unique_ptr<ResizeComponentImpl> data;
};

#endif