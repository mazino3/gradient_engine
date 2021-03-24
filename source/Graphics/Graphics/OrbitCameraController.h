#ifndef GRAPHICS_ORBIT_CAMERA_CONTROLLER_H
#define GRAPHICS_ORBIT_CAMERA_CONTROLLER_H

#include <Graphics/Camera.h>
#include <Graphics/InputClientBase.h>
#include <memory>
#include <glm/vec3.hpp>

struct OrbitCameraControllerImpl;

struct OrbitCameraController
{
	OrbitCameraController(Camera& camera);
	
	void update(float dt);
	void setDistance(float distance);
	void setMaxDistance(float maxDistance);
	void setHorizontalAngle(float angle);
	void setVerticalAngle(float angle);
	void setRootPosition(const glm::vec3& position);
	void setSensitivity(float sensitivity);

	InputClientBase& getInputClient();

private:
	std::shared_ptr<OrbitCameraControllerImpl> data;
};

#endif