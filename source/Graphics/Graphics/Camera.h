#ifndef GRAPHICS_CAMERA_H
#define GRAPHICS_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <memory>
#include <Math/Geometry/Ray.h>

struct CameraImpl;

enum class CameraType
{
	None,
	Ortho,
	Perspective
};

struct Camera
{
	glm::vec3 position;
	glm::vec3 dirFront;
	glm::vec3 dirUp;

	Camera();
	Camera& operator=(const Camera& other);

	void setPerspective(float fov, float ratio, float nearPlane, float farPlane);
	void setOrtho(float left, float right, float bottom, float top, float nearPlane, float farPlane);
	CameraType getCameraType();

	glm::mat4x4 getProjectionMatrix();
	glm::mat4x4 getViewMatrix();
	glm::mat4x4 getRotationMatrix();

	Camera getDirectionalLightCamera(const glm::vec3& lightDirection, float shadowDistance);
	Ray getMouseRay(float normalizedScreenX, float normalizedScreenY);
	Ray getMouseRay(const glm::vec2& normalizedScreenPos);

private:

	std::shared_ptr<CameraImpl> _data;
};

#endif