#include <glm/ext.hpp>
#include <cmath>
#include <algorithm>
#include "FreeCameraController.h"
#include "KeyCodes.h"
#include "InputClient.h"

static const float PI = 3.14159265f;

struct FreeCameraControllerImpl
{
	Camera& camera;
	float sensitivity;
	float horizontalAngle; //in radians
	float verticalAngle;
	float speed;
	bool onlyRotationMode;

	InputClient inputClient;

	bool isDragging;
	double prevXpos;
	double prevYpos;

	bool forward;
	bool backward;
	bool left;
	bool right;

	FreeCameraControllerImpl(Camera& camera) :
		camera(camera),
		sensitivity(0.5f),
		horizontalAngle(0.0f),
		verticalAngle(0.0f),
		speed(3.0f),
		onlyRotationMode(true),
		isDragging(false),
		prevXpos(0.0),
		prevYpos(0.0),
		forward(false),
		backward(false),
		left(false),
		right(false)
	{}

	glm::vec3 getMovementDirection();
};

static bool isMovementKey(int keycode)
{
	switch (keycode)
	{
	case KEYCODE_KEY_W:
	case KEYCODE_KEY_A:
	case KEYCODE_KEY_S:
	case KEYCODE_KEY_D:
		return true;
	default:
		return false;
	}
}

FreeCameraController::FreeCameraController(Camera& camera)
{
	data = std::make_shared<FreeCameraControllerImpl>(camera);
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

			float horizontalDelta = -deltaX * data->sensitivity * PI / 180.0f;
			float verticalDelta = deltaY * data->sensitivity * PI / 180.0f;
			data->horizontalAngle += horizontalDelta;
			data->verticalAngle = std::max(std::min(data->verticalAngle + verticalDelta, PI / 2), -PI / 2);
			return true;
		}
		else
		{
			return false;
		}
	});

	auto keyCallback = [this](int keycode, bool pressed) 
	{
		if (isMovementKey(keycode) && !data->onlyRotationMode)
		{
			switch (keycode)
			{
			case KEYCODE_KEY_W:
				data->forward = pressed;
				break;
			case KEYCODE_KEY_S:
				data->backward = pressed;
				break;
			case KEYCODE_KEY_A:
				data->left = pressed;
				break;
			case KEYCODE_KEY_D:
				data->right = pressed;
				break;
			}
			return true;
		}
		else
		{
			return false;
		}
	};

	using namespace std::placeholders;

	data->inputClient.onKeyPressed(std::bind(keyCallback, _1, true));
	data->inputClient.onKeyReleased(std::bind(keyCallback, _1, false));
}

glm::vec3 FreeCameraControllerImpl::getMovementDirection()
{
	glm::vec3 result(0, 0, 0);
	glm::vec3 dirForward = camera.dirFront;
	glm::vec3 dirLeft = glm::cross(camera.dirUp, camera.dirFront);

	if (forward) result += dirForward;
	if (backward) result -= dirForward;
	if (left) result += dirLeft;
	if (right) result -= dirLeft;

	if (result.length() > 0.0001f)
	{
		result /= result.length();
	}

	return result;
}

void FreeCameraController::update(float dt)
{
	glm::vec3 movementDir = data->getMovementDirection();
	data->camera.position += movementDir * data->speed * dt;

	float verticalAngleUp = data->verticalAngle + PI / 2;
	glm::mat4x4 rotMatrix = glm::rotate(glm::mat4x4(1.0f), data->horizontalAngle, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::vec4 dirFront = glm::vec4(cosf(data->verticalAngle), 0, sinf(data->verticalAngle), 1.0f);
	glm::vec4 dirUp = glm::vec4(cosf(verticalAngleUp), 0, sinf(verticalAngleUp), 1.0f);

	dirFront = rotMatrix * dirFront;
	dirUp = rotMatrix * dirUp;

	data->camera.dirFront = dirFront;
	data->camera.dirUp = dirUp;
}

void FreeCameraController::setOnlyRotationMode(bool onlyRotationMode)
{
	data->onlyRotationMode = onlyRotationMode;
}

void FreeCameraController::setSensitivity(float sensitivity)
{
	data->sensitivity = sensitivity;
}

void FreeCameraController::setSpeed(float speed)
{
	data->speed = speed;
}

static float getAngle(const glm::vec2& direction)
{
	static const float EPS = 0.00001f;

	if (std::fabsf(direction.x) < EPS)
	{
		return direction.y > 0 ? 0 : PI;
	}

	if (direction.x < 0)
	{
		return std::atanf(direction.y / direction.x) + PI;
	}
	else
	{
		if (direction.y > 0)
		{
			return std::atanf(direction.y / direction.x);
		}
		else
		{
			return std::atanf(direction.y / direction.x) + PI * 2;
		}
	}
}

static float getVerticalAngle(const glm::vec2& direction)
{
	if (std::fabsf(direction.x) < 0.0001f)
	{
		if (direction.y > 0)
		{
			return PI / 2;
		}
		else
		{
			return -PI / 2;
		}
	}

	return std::atanf(direction.y / direction.x);
}

void FreeCameraController::setCameraDirection(const glm::vec3& direction)
{
	glm::vec2 dirHorizontal(direction.x, direction.y);
	float horizontalLength = glm::length(dirHorizontal);
	if (horizontalLength > 0.00001f)
	{
		dirHorizontal /= horizontalLength;
	}
	data->horizontalAngle = getAngle(dirHorizontal);
	glm::vec2 dirVertical(horizontalLength, direction.z);
	data->verticalAngle = getVerticalAngle(dirVertical);
}

InputClientBase& FreeCameraController::getInputClient()
{
	return data->inputClient;
}

