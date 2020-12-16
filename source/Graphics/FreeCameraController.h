#ifndef GRAPHICS_FREE_CAMERA_CONTROLLER_H
#define GRAPHICS_FREE_CAMERA_CONTROLLER_H

#include "Camera.h"
#include "InputClientBase.h"
#include <memory>

struct FreeCameraControllerImpl;

struct FreeCameraController
{
	FreeCameraController(Camera& camera);

	void update(float dt);
	void setOnlyRotationMode(bool onlyRotationMode);
	void setSensitivity(float sensitivity);
	void setSpeed(float speed);

	InputClientBase& getInputClient();

private:
	std::shared_ptr<FreeCameraControllerImpl> data;
};

#endif