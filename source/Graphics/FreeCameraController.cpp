#include "FreeCameraController.h"
#include "KeyCodes.h"
#include "InputClient.h"

struct FreeCameraControllerImpl
{
	Camera& camera;
	float sensitivity;
	bool onlyRotationMode;

	InputClient inputClient;

	bool isDragging;
	double prevXpos;
	double prevYpos;

	FreeCameraControllerImpl(Camera& camera) :
		camera(camera),
		sensitivity(0.5f),
		onlyRotationMode(true),
		isDragging(false),
		prevXpos(0.0),
		prevYpos(0.0)
	{}
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

	data->inputClient.onKeyPressed([this](int keycode) 
	{
		if (isMovementKey(keycode) && !data->onlyRotationMode)
		{
			//todo: update movement
			return true;
		}
		else
		{
			return false;
		}
	});

	data->inputClient.onKeyReleased([this](int keycode) 
	{
		if (isMovementKey(keycode) && !data->onlyRotationMode)
		{
			//todo: update movement
			return true;
		}
		else
		{
			return false;
		}
	});
}

void FreeCameraController::update(float dt)
{
	//todo: implement
}

void FreeCameraController::setOnlyRotationMode(bool onlyRotationMode)
{
	data->onlyRotationMode = onlyRotationMode;
}

void FreeCameraController::setSensitivity(float sensitivity)
{
	data->sensitivity = sensitivity;
}

InputClientBase& FreeCameraController::getInputClient()
{
	return data->inputClient;
}

