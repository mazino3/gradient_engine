#include "ResizeManager.h"
#include <glm/vec2.hpp>
#include <glm/ext.hpp>
#include <Graphics/Camera.h>
#include <istream>

struct ResizeManagerImpl
{
	//todo: implement
	InputClient inputClient;
	
	bool isDragging;
	bool isFirstMove;
	ArrowType currentArrowType;
	Plane currentPlane;
	LevelObject* currentObject;

	double prevMouseX;
	double prevMouseY;

	double windowSizeX;
	double windowSizeY;

	Camera& camera;

	ResizeManagerImpl(Camera& camera) :
		isDragging(false),
		camera(camera)
	{}

	glm::vec2 getNormalizedMousePos(double mouseX, double mouseY);
};

glm::vec2 ResizeManagerImpl::getNormalizedMousePos(double mouseX, double mouseY)
{
	double normalizedX = mouseX / windowSizeX;
	double normalizedY = mouseY / windowSizeY;

	normalizedX -= 0.5;
	normalizedY = 0.5 - normalizedY;
	normalizedX *= 2;
	normalizedY *= 2;

	return glm::vec2(normalizedX, normalizedY);
}

ResizeManager::ResizeManager(double windowSizeX, double windowSizeY, Camera& camera)
{
	data = std::make_unique<ResizeManagerImpl>(camera);

	data->windowSizeX = windowSizeX;
	data->windowSizeY = windowSizeY;

	data->inputClient.onWindowSizeChanged([this](double windowSizeX, double windowSizeY) 
	{
		data->windowSizeX = windowSizeX;
		data->windowSizeY = windowSizeY;
		return false;
	});

	data->inputClient.onMouseMoved([this](double mouseX, double mouseY) 
	{
			if (!data->isDragging)
			{
				return false;
			}

			if (data->isFirstMove)
			{
				data->prevMouseX = mouseX;
				data->prevMouseY = mouseY;
				data->isFirstMove = false;
			}
			else
			{
				glm::vec2 oldMousePos = data->getNormalizedMousePos(data->prevMouseX, data->prevMouseY);
				glm::vec2 newMousePos = data->getNormalizedMousePos(mouseX, mouseY);

				Ray oldRay = data->camera.getMouseRay(oldMousePos);
				Ray newRay = data->camera.getMouseRay(newMousePos);

				data->prevMouseX = mouseX;
				data->prevMouseY = mouseY;

				glm::vec3 oldHit;
				glm::vec3 newHit;

				if (!data->currentPlane.intersectsWith(oldRay, oldHit))
				{
					std::cout << "old hit not intersecting" << std::endl;
					return true;
				}
				if (!data->currentPlane.intersectsWith(newRay, newHit))
				{
					std::cout << "new hit not intersecting" << std::endl;
					return true;
				}

				glm::vec3 delta = newHit - oldHit;
				glm::vec3 deltaProjection;
				switch (data->currentArrowType)
				{
					case ArrowType::MINUS_X:
					case ArrowType::PLUS_X:
						deltaProjection = glm::vec3(delta.x, 0, 0);
						break;
					case ArrowType::MINUS_Y:
					case ArrowType::PLUS_Y:
						deltaProjection = glm::vec3(0, delta.y, 0);
						break;
					case ArrowType::MINUS_Z:
					case ArrowType::PLUS_Z:
						deltaProjection = glm::vec3(0, 0, delta.z);
						break;
				}

				std::cout << "delta: " << delta.x << " " << delta.y << " " << delta.z << std::endl;

				glm::vec3 newScale = data->currentObject->getScale() + deltaProjection;
				data->currentObject->setScale(newScale);
			}
			return true;
	});

	data->inputClient.onMouseReleased([this](double mouseX, double mouseY, int button) 
		{
			if (data->isDragging)
			{
				data->isDragging = false;
				return true;
			}
			else
			{
				return false;
			}
		});
}

ResizeManager::~ResizeManager()
{
}

InputClient& ResizeManager::getInputClient()
{
	return data->inputClient;
}

void ResizeManager::startDragging(LevelObject& levelObject, ArrowType arrowType, Plane arrowPlane)
{
	data->isDragging = true;
	data->isFirstMove = true;
	data->currentArrowType = arrowType;
	data->currentPlane = arrowPlane;
	data->currentObject = &levelObject;

	std::cout << "dragging started" << std::endl;
}