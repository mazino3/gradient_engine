#include <glm/ext.hpp>
#include "FreeCameraController.h"
#include "KeyCodes.h"
#include "InputClient.h"

struct FreeCameraControllerImpl
{
	Camera& camera;
	float sensitivity;
	float horizontalAngle;
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
			//todo: start dragging
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
			//todo: stop dragging
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
			//todo: do dragging
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

InputClientBase& FreeCameraController::getInputClient()
{
	return data->inputClient;
}

