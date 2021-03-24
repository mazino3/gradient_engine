#include <Graphics/Transform.h>
#include <glm/ext.hpp>

Transform::Transform() : 
	scale(1, 1, 1),
	position(0, 0, 0),
	rotation(0, 0, 0)
{}

glm::mat4x4 Transform::getWorldMatrix() const
{
	glm::mat4x4 matScale = glm::scale(glm::mat4x4(1.0f), scale);
	glm::mat4x4 matRotateX = glm::rotate(glm::mat4x4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4x4 matRotateY = glm::rotate(glm::mat4x4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4x4 matRotateZ = glm::rotate(glm::mat4x4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4x4 matRotate = matRotateZ * matRotateY * matRotateX;
	glm::mat4x4 matTranslate = glm::translate(glm::mat4x4(1.0f), position);

	return matTranslate * matRotate * matScale;
}