#include "Camera.h"
#include <glm/ext.hpp>

struct CameraImpl
{
	glm::mat4x4 projectionMatrix;
	CameraType type;

	CameraImpl() :
		type(CameraType::None),
		projectionMatrix(1.0f)
	{}
};

Camera::Camera()
{
	_data = std::make_shared<CameraImpl>();
}

void Camera::setPerspective(float fov, float ratio, float nearPlane, float farPlane)
{
	_data->type = CameraType::Perspective;
	_data->projectionMatrix = glm::perspective(fov, ratio, nearPlane, farPlane);
}

void Camera::setOrtho(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
	_data->type = CameraType::Ortho;
	_data->projectionMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
}

glm::mat4x4 Camera::getProjectionMatrix()
{
	return _data->projectionMatrix;
}

glm::mat4x4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position + dirFront, dirUp);
}

glm::mat4x4 Camera::getNormalMatrix()
{
	return glm::transpose(glm::inverse(getViewMatrix()));
}

