#ifndef RESIZE_MANAGER_H
#define RESIZE_MANAGER_H

#include <memory>
#include <Graphics/InputClient.h>
#include <Math/Geometry/Plane.h>
#include <Math/Geometry/Ray.h>
#include "ResizeComponent.h"
#include "LevelObject.h"

struct ResizeManagerImpl;

enum class ArrowType;

struct ResizeManager
{
	ResizeManager(double windowSizeX, double windowSizeY, Camera& camera);
	~ResizeManager();

	InputClient& getInputClient();
	void startDragging(LevelObject& levelObject, ArrowType arrowType, Plane arrowPlane);
	void update();
private:
	std::unique_ptr<ResizeManagerImpl> data;
};

#endif