#ifndef GRAPHICS_SIMPLE_SHADER_3D
#define GRAPHICS_SIMPLE_SHADER_3D

#include <Graphics/Shaders/Shader.h>

struct SimpleShader3d : Shader
{
	SimpleShader3d();

	void setProjectionMatrix(const glm::mat4x4& matrix);
	void setViewMatrix(const glm::mat4x4& matrix);
	void setModelMatrix(const glm::mat4x4& matrix);
	void setNormalMatrix(const glm::mat4x4& matrix);

	void setEyeDirection(const glm::vec3& eyeDirection);

	void setColor(const glm::vec3& color);

};

#endif