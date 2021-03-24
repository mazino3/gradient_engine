#include <Graphics/OrbitCameraController.h>
#include <Graphics/InputClient.h>
#include <Graphics/KeyCodes.h>
#include <cmath>
#include <algorithm>
#include <glm/ext.hpp>
#include <iostream>

struct OrbitCameraControllerImpl
{
	Camera& camera;
	float distance;
	float maxDistance;
	float horizontalAngle; //in degrees
	float verticalAngle;
	float sensitivity;
	float distanceSensitivity;
	glm::vec3 rootPosition;

	InputClient inputClient;
	
	bool isDragging;
	double prevXpos;
	double prevYpos;

	OrbitCameraControllerImpl(Camera& camera) :
		camera(camera),
		distance(10.0f),
		maxDistance(50.0f),
		horizontalAngle(0.0f),
		verticalAngle(45.0f),
		isDragging(false),
		prevXpos(0.0),
		prevYpos(0.0),
		sensitivity(0.5f),
		distanceSensitivity(1),
		rootPosition(0.0f, 0.0f, 0.0f)
	{}
};

OrbitCameraController::OrbitCameraController(Camera& camera)
{
	data = std::make_shared<OrbitCameraControllerImpl>(camera);
	data->inputClient.onMousePressed([this](double xpos, double ypos, int button) 
	{
		if (button == KEYCODE_MOUSE_BUTTON_2)
		{
			data->isDragging = true;
			data->prevXpos = xpos;
			data->prevYpos = ypos;
			return true;
		}
		else
		{
			return false;
		}
	});
	data->inputClient.onMouseReleased([this](double xpos, double ypos, int button) 
	{
		if (button == KEYCODE_MOUSE_BUTTON_2 && data->isDragging)
		{
			data->isDragging = false;
			return true;
		}
		else
		{
			return false;
		}
	});
	data->inputClient.onMouseMoved([this](double xpos, double ypos) 
	{
		if (data->isDragging)
		{
			double deltaX = xpos - data->prevXpos;
			double deltaY = ypos - data->prevYpos;
			data->prevXpos = xpos;
			data->prevYpos = ypos;

			float horizontalDelta = -deltaX * data->sensitivity;
			float verticalDelta = deltaY * data->sensitivity;
			data->horizontalAngle += horizontalDelta;
			data->verticalAngle = std::max(std::min(data->verticalAngle + verticalDelta, 90.0f), 0.0f);

			return true;
		}
		else
		{
			return false;
		}
	});
	data->inputClient.onMouseScrolled([this](double xoffset, double yoffset) 
	{
		data->distance = std::max(1.0, std::min(data->distance - yoffset * data->distanceSensitivity, (double) data->maxDistance));
		return true;
	});
}

static float toRadians(float degrees)
{
	const static float PI = 3.1415926536f;
	return degrees / 180.0f * PI;
}

void OrbitCameraController::update(float dt)
{
	float horizontalRadians = toRadians(data->horizontalAngle);
	float verticalRadiansUp = toRadians(data->verticalAngle + 90.0f);
	float verticalRadians = toRadians(data->verticalAngle);
	glm::mat4x4 rotMatrix = glm::rotate(glm::mat4x4(1.0f), horizontalRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::vec4 dirFront = glm::vec4(cosf(verticalRadians), 0, sinf(verticalRadians), 1.0f);
	glm::vec4 dirUp = glm::vec4(cosf(verticalRadiansUp), 0, sinf(verticalRadiansUp), 1.0f);

	dirFront = rotMatrix * dirFront;
	dirFront = -dirFront;
	dirUp = rotMatrix * dirUp;

	data->camera.dirFront = dirFront;
	data->camera.dirUp = dirUp;
	data->camera.position = data->rootPosition - glm::vec3(dirFront) * data->distance;
}

InputClientBase& OrbitCameraController::getInputClient()
{
	return data->inputClient;
}

void OrbitCameraController::setDistance(float distance)
{
	data->distance = distance;
}

void OrbitCameraController::setMaxDistance(float maxDistance)
{
	data->maxDistance = maxDistance;
}

void OrbitCameraController::setHorizontalAngle(float horizontalAngle)
{
	data->horizontalAngle = horizontalAngle;
}

void OrbitCameraController::setVerticalAngle(float verticalAngle)
{
	data->verticalAngle = verticalAngle;
}

void OrbitCameraController::setRootPosition(const glm::vec3& position)
{
	data->rootPosition = position;
}

void OrbitCameraController::setSensitivity(float sensitivity)
{
	data->sensitivity = sensitivity;
}
