#include "Camera.h"
#include <glm/ext.hpp>
#include <vector>
#include <iostream>
#include <cmath>

struct CameraImpl
{
	glm::mat4x4 projectionMatrix;
	CameraType type;

	CameraImpl() :
		type(CameraType::None),
		projectionMatrix(1.0f)
	{}

	glm::vec3 frustumPoints[8] = {};

	struct PerspectiveParams
	{
		float fov;
		float ratio;
		float nearPlane;
		float farPlane;

		PerspectiveParams() :
			fov(0), ratio(0), nearPlane(0), farPlane(0) {}
	} perspectiveParams;
};

Camera::Camera()
{
	_data = std::make_shared<CameraImpl>();
}

void Camera::setPerspective(float fov, float ratio, float nearPlane, float farPlane)
{
	_data->type = CameraType::Perspective;
	_data->projectionMatrix = glm::perspective(fov, ratio, nearPlane, farPlane);
	_data->perspectiveParams.fov = fov;
	_data->perspectiveParams.ratio = ratio;
	_data->perspectiveParams.nearPlane = nearPlane;
	_data->perspectiveParams.farPlane = farPlane;
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

glm::mat4x4 Camera::getRotationMatrix()
{
	glm::mat4x4 result = glm::mat4(glm::mat3(getViewMatrix()));
	return result;
}

CameraType Camera::getCameraType()
{
	return _data->type;
}

static glm::vec3 getLightDirUp(const glm::vec3& lightDirection)
{
	//todo: implement
}

Camera Camera::getDirectionalLightCamera(const glm::vec3& lightDirection, float shadowDistance)
{
	static glm::vec3 frustumPoints[8];
	Camera result;
	
	//computing frustum points
	
	float nearPlane = _data->perspectiveParams.nearPlane;
	float farPlane = _data->perspectiveParams.farPlane;
	float yNear = std::tanf(_data->perspectiveParams.fov / 2.0f) * nearPlane;
	float xNear = yNear * _data->perspectiveParams.ratio;
	float yFar = std::tanf(_data->perspectiveParams.fov / 2.0f) * shadowDistance;
	float xFar = yFar * _data->perspectiveParams.ratio;

	glm::vec3 dirRight = glm::cross(dirFront, dirUp);

	frustumPoints[0] = position + dirFront * nearPlane - dirUp * yNear - dirRight * xNear;
	frustumPoints[1] = position + dirFront * nearPlane - dirUp * yNear + dirRight * xNear;
	frustumPoints[2] = position + dirFront * nearPlane + dirUp * yNear - dirRight * xNear;
	frustumPoints[3] = position + dirFront * nearPlane + dirUp * yNear + dirRight * xNear;

	frustumPoints[4] = position + dirFront * shadowDistance - dirUp * yFar - dirRight * xFar;
	frustumPoints[5] = position + dirFront * shadowDistance - dirUp * yFar + dirRight * xFar;
	frustumPoints[6] = position + dirFront * shadowDistance + dirUp * yFar - dirRight * xFar;
	frustumPoints[7] = position + dirFront * shadowDistance + dirUp * yFar + dirRight * xFar;

	//todo: transform frustum points to eye space of light

	return result;
}
