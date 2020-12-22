#include "Camera.h"
#include <glm/ext.hpp>
#include <vector>
#include <iostream>

struct CameraImpl
{
	glm::mat4x4 projectionMatrix;
	CameraType type;

	CameraImpl() :
		type(CameraType::None),
		projectionMatrix(1.0f)
	{}

	std::vector<glm::vec3> frustumPoints;
};

Camera::Camera()
{
	_data = std::make_shared<CameraImpl>();
}

void Camera::setPerspective(float fov, float ratio, float nearPlane, float farPlane)
{
	_data->type = CameraType::Perspective;
	_data->projectionMatrix = glm::perspective(fov, ratio, nearPlane, farPlane);

	_data->frustumPoints.clear();
	
	//todo: compute frustum points
}

void Camera::setOrtho(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
	_data->type = CameraType::Ortho;
	_data->projectionMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);

	_data->frustumPoints.clear();

	//todo: compute frustum points
}

glm::mat4x4 Camera::getProjectionMatrix()
{
	return _data->projectionMatrix;
}

glm::mat4x4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position + dirFront, dirUp);
}

CameraType Camera::getCameraType()
{
	return _data->type;
}

Camera Camera::getDirectionalLightCamera(const glm::vec3& lightDirection)
{
	Camera result;
	
	//todo: implement

	return result;
}
