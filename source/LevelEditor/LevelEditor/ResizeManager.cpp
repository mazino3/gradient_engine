#include "ResizeManager.h"
#include <glm/vec2.hpp>
#include <glm/ext.hpp>
#include <Graphics/Camera.h>
#include <istream>
#include <Utility/SnappingProperty.h>

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

	SnappingProperty scaleProp;

	ResizeManagerImpl(Camera& camera) :
		isDragging(false),
		camera(camera),
		scaleProp(1.0f)
	{}

	glm::vec2 getNormalizedMousePos(double mouseX, double mouseY);
	glm::vec3 getScaleDir();
	float getArrowDir();
};

glm::vec3 ResizeManagerImpl::getScaleDir()
{
	glm::vec3 result;
	switch (currentArrowType)
	{
	case ArrowType::MINUS_X:
	case ArrowType::PLUS_X:
		result = glm::vec3(1, 0, 0);
		break;
	case ArrowType::MINUS_Y:
	case ArrowType::PLUS_Y:
		result = glm::vec3(0, 1, 0);
		break;
	case ArrowType::MINUS_Z:
	case ArrowType::PLUS_Z:
		result = glm::vec3(0, 0, 1);
		break;
	}
	return result;
}

float ResizeManagerImpl::getArrowDir()
{
	switch (currentArrowType)
	{
		case ArrowType::MINUS_X:
		case ArrowType::MINUS_Y:
		case ArrowType::MINUS_Z:
			return -1.0f;
		case ArrowType::PLUS_X:
		case ArrowType::PLUS_Y:
		case ArrowType::PLUS_Z:
			return 1.0f;
	}
}

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

	data->scaleProp.setCurrentWeight(0.6f);

	data->scaleProp.onValueChanged([this](float oldValue, float newValue) 
		{
			if (!data->isDragging)
			{
				return;
			}
			glm::vec3 deltaProjection = data->getScaleDir() * (newValue - oldValue);
			float dir = data->getArrowDir();
			deltaProjection = deltaProjection * dir;
			glm::vec3 newScale = data->currentObject->getScale() + deltaProjection;
			data->currentObject->setScale(newScale);
			data->currentObject->setPosition(data->currentObject->getPosition() + deltaProjection * 0.5f * dir);
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
				glm::vec3 deltaProjection = data->getScaleDir() * delta;
				float sign = (deltaProjection.x + deltaProjection.y + deltaProjection.z);
				sign = sign / std::fabsf(sign);
				float deltaMagnitude = glm::length(deltaProjection) * sign;
				data->scaleProp.setTargetValue(data->scaleProp.getTargetValue() + deltaMagnitude);
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
	
	glm::vec3 scale = levelObject.getScale();
	float scaleMagnitude = glm::length(scale * data->getScaleDir());
	data->scaleProp.setCurrentValue(scaleMagnitude);
	data->scaleProp.setTargetValue(scaleMagnitude);

	std::cout << "dragging started" << std::endl;
}

void ResizeManager::update()
{
	data->scaleProp.update();
}