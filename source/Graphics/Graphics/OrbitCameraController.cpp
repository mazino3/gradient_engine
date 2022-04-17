#include <Graphics/OrbitCameraController.h>
#include <Graphics/InputClient.h>
#include <Graphics/KeyCodes.h>
#include <Math/Geometry/Plane.h>
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
	bool isSpacePressed;
	double prevXpos;
	double prevYpos;

	float screenSizeX;
	float screenSizeY;

	OrbitCameraControllerImpl(Camera& camera) :
		camera(camera),
		distance(10.0f),
		maxDistance(50.0f),
		horizontalAngle(0.0f),
		verticalAngle(45.0f),
		isDragging(false),
		isSpacePressed(false),
		prevXpos(0.0),
		prevYpos(0.0),
		sensitivity(0.5f),
		distanceSensitivity(1),
		rootPosition(0.0f, 0.0f, 0.0f),
		screenSizeX(0.0f),
		screenSizeY(0.0f)
	{}

	glm::vec2 getNormalizedMousePos(float x, float y);
};

glm::vec2 OrbitCameraControllerImpl::getNormalizedMousePos(float x, float y)
{
	double normalizedX = x / screenSizeX;
	double normalizedY = y / screenSizeY;

	normalizedX -= 0.5;
	normalizedY = 0.5 - normalizedY;
	normalizedX *= 2;
	normalizedY *= 2;

	return glm::vec2(normalizedX, normalizedY);
}

OrbitCameraController::OrbitCameraController(Camera& camera, float screenSizeX, float screenSizeY)
{
	data = std::make_shared<OrbitCameraControllerImpl>(camera);
	data->screenSizeX = screenSizeX;
	data->screenSizeY = screenSizeY;

	data->inputClient.onWindowSizeChanged([this](int newWidth, int newHeight) 
	{
		data->screenSizeX = newWidth;
		data->screenSizeY = newHeight;
		return false;
	});

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
			if (data->isSpacePressed)
			{
				glm::vec3 oldGroundPoint;
				glm::vec3 newGroundPoint;

				glm::vec2 oldNormalizedMousePos = data->getNormalizedMousePos(data->prevXpos, data->prevYpos);
				glm::vec2 newNormalizedMousePos = data->getNormalizedMousePos(xpos, ypos);

				Ray oldRay = data->camera.getMouseRay(oldNormalizedMousePos);
				Ray newRay = data->camera.getMouseRay(newNormalizedMousePos);

				if (!Plane::PLANE_XY.intersectsWith(oldRay, oldGroundPoint) || !Plane::PLANE_XY.intersectsWith(newRay, newGroundPoint))
				{
					return false;
				}

				glm::vec3 delta = newGroundPoint - oldGroundPoint;
				delta.z = 0;
				data->rootPosition -= delta;
			}
			else
			{
				double deltaX = xpos - data->prevXpos;
				double deltaY = ypos - data->prevYpos;
				

				float horizontalDelta = -deltaX * data->sensitivity;
				float verticalDelta = deltaY * data->sensitivity;
				data->horizontalAngle += horizontalDelta;
				data->verticalAngle = std::max(std::min(data->verticalAngle + verticalDelta, 90.0f), 0.0f);
			}

			data->prevXpos = xpos;
			data->prevYpos = ypos;

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
	data->inputClient.onKeyPressed([this](int keyCode) 
	{
		if (keyCode == KEYCODE_KEY_SPACE)
		{
			data->isSpacePressed = true;
		}
		return false;
	});
	data->inputClient.onKeyReleased([this](int keyCode) 
	{
		if (keyCode == KEYCODE_KEY_SPACE)
		{
			data->isSpacePressed = false;
		}
		return false;
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
