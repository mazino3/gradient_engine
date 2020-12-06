#include "OrbitCameraController.h"
#include "InputClient.h"
#include "KeyCodes.h"
#include <math.h>
#include <glm/ext.hpp>

struct OrbitCameraControllerImpl
{
	Camera& camera;
	float distance;
	float maxDistance;
	float horizontalAngle;
	float verticalAngle;
	float sensitivity;
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
		sensitivity(0.01f),
		rootPosition(0.0f, 0.0f, 0.0f)
	{}
};

OrbitCameraController::OrbitCameraController(Camera& camera)
{
	data = std::make_shared<OrbitCameraControllerImpl>(camera);
	data->inputClient.onMousePressed([this](double xpos, double ypos, int button) 
	{
		if (button == KEYCODE_MOUSE_BUTTON_1)
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
		if (button == KEYCODE_MOUSE_BUTTON_1 && data->isDragging)
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

			float horizontalDelta = deltaX * data->sensitivity;
			float verticalDelta = deltaY * data->sensitivity;
			data->horizontalAngle += horizontalDelta;
			data->verticalAngle += verticalDelta;

			return true;
		}
		else
		{
			return false;
		}
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

