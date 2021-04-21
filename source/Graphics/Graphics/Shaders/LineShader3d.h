#ifndef GRAPHICS_LINE_SHADER_3D
#define GRAPHICS_LINE_SHADER_3D

#include <Graphics/Shaders/Shader.h>

struct LineShader3d : Shader
{
	LineShader3d();

	void setProjectionMatrix(const glm::mat4x4& matrix);
	void setViewMatrix(const glm::mat4x4& matrix);
	
	void setPos1(const glm::vec3& pos);
	void setPos2(const glm::vec3& pos);

	void setColor(const glm::vec3& color);
};

#endif