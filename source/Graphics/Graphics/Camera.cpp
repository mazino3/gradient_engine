#include "Camera.h"
#include <glm/ext.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>

struct CameraImpl
{
	glm::mat4x4 projectionMatrix;
	CameraType type;

	CameraImpl() :
		type(CameraType::None),
		projectionMatrix(1.0f)
	{}

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

Camera& Camera::operator=(const Camera& other)
{
	position = other.position;
	dirFront = other.dirFront;
	dirUp = other.dirUp;
	*_data = *other._data;
	return *this;
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
	Camera resultLightCamera;
	
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

	glm::vec3 cameraRight = glm::cross(lightDirection, glm::vec3(0, 0, 1));
	if (glm::length(cameraRight) < 0.00001) //light is straight up or straight down
	{
		cameraRight = glm::vec3(1, 0, 0);
	}
	resultLightCamera.dirFront = lightDirection;
	resultLightCamera.dirUp = glm::normalize(glm::cross(lightDirection, cameraRight));
	resultLightCamera.position = glm::vec3(0, 0, 0);
	
	glm::mat4x4 lightViewMatrix = resultLightCamera.getViewMatrix();

	float minX = std::numeric_limits<float>::infinity();
	float minY = std::numeric_limits<float>::infinity();
	float minZ = std::numeric_limits<float>::infinity();
	float maxX = -std::numeric_limits<float>::infinity();
	float maxY = -std::numeric_limits<float>::infinity();
	float maxZ = -std::numeric_limits<float>::infinity();

	for (int i = 0; i < 8; i++)
	{
		frustumPoints[i] = lightViewMatrix * glm::vec4(frustumPoints[i], 1.0f);
	}

	for (const auto& point : frustumPoints)
	{
		minX = std::fminf(minX, point.x);
		minY = std::fminf(minY, point.y);
		minZ = std::fminf(minZ, point.z);
		maxX = std::fmaxf(maxX, point.x);
		maxY = std::fmaxf(maxY, point.y);
		maxZ = std::fmaxf(maxZ, point.z);
	}

	glm::vec3 size(maxX - minX, maxY - minY, maxZ - minZ);

	glm::mat4x4 inverseLightView = glm::inverse(lightViewMatrix);
	resultLightCamera.position = inverseLightView * glm::vec4((minX + maxX) / 2, (minY + maxY) / 2, (minZ + maxZ) / 2, 1.0f);
	resultLightCamera.setOrtho(-size.x / 2, size.x / 2, -size.y / 2, size.y / 2, -size.z / 2 - 10, size.z / 2);

	return resultLightCamera;
}
