#ifndef RESIZE_MANAGER_H
#define RESIZE_MANAGER_H

#include <memory>
#include <Graphics/InputClient.h>
#include <Math/Geometry/Plane.h>
#include <Math/Geometry/Ray.h>
#include "LevelObject.h"
#include "ResizeComponent.h"

struct ResizeManagerImpl;

struct ResizeManager
{
	ResizeManager();
	~ResizeManager();

	InputClient& getInputClient();
	void startDragging(LevelObject& levelObject, ArrowType arrowType, Plane arrowPlane);
private:
	std::unique_ptr<ResizeManagerImpl> data;
};

#endif