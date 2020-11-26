#include "Shader3d.h"
#include <string>

static std::string vertexShader =
"#version 130\n"
""
"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"uniform mat4 model;\n"
"uniform mat4 normalTm;\n"
""
"in vec3 in_Position;\n"
"in vec4 in_Color;\n"
"in vec2 in_TexCoord;\n"
"in vec3 in_Normal;\n"
"out vec4 ex_Color;\n"
"out vec2 ex_TexCoord;\n"
"out vec3 ex_Normal;\n"
"out vec3 ex_VertPos;\n"
"void main(void) {\n"
"	gl_Position = projection * view * model * vec4(in_Position, 1.0);\n"
"	ex_Color = in_Color;\n"
"	ex_TexCoord = in_TexCoord;\n"
"	ex_Normal = (normalTm * vec4(in_Normal, 1.0)).xyz;\n"
"	ex_VertPos = (view * model * vec4(in_Position, 1.0)).xyz;\n"
"}";

static std::string fragmentShader =
"#version 130\n"
"precision highp float;\n"
""
"struct MaterialProperties {\n"
"	vec3 emission;\n"
"	vec3 ambient;\n"
"	vec3 diffuse;\n"
"	vec3 specular;\n"
"	float shininess;\n"
"};\n"
""
"struct DirectionalLight {\n"
"	vec3 direction;\n"
"	vec3 ambientColor;\n"
"	vec3 diffuseColor;\n"
"	vec3 specularColor;\n"
"};\n"
""
"uniform int directionalLightsCount;"
"uniform DirectionalLight directionalLights[16];"
""
"uniform int materialIndex;\n"
"uniform MaterialProperties materials[16];\n"
"uniform vec3 eyeDirection;\n"
"uniform sampler2D diffuseTex;\n"
"in vec4 ex_Color;\n"
"in vec2 ex_TexCoord;\n"
"in vec3 ex_Normal;\n"
"in vec3 ex_VertPos;\n"
"out vec4 gl_FragColor;\n"
"void main(void) {\n"
"	vec3 resultColor = vec3(0.0, 0.0, 0.0);\n"
"	vec3 normal = normalize(ex_Normal);\n"
"	vec3 eyeDir = normalize(-ex_VertPos);\n"
"	for (int i = 0; i < directionalLightsCount; i++) {\n"
"		vec3 reflection = normalize(reflect(-directionalLights[i].direction, normal));\n"
"		float cosTheta = dot(directionalLights[i].direction, normal);\n"
"		float cosPhi = dot(eyeDir, reflection);\n"
"		vec3 diffuse = directionalLights[i].diffuseColor * materials[materialIndex].diffuse * max(cosTheta, 0.0);\n"
"		vec3 specular = directionalLights[i].specularColor * materials[materialIndex].specular * pow(max(cosPhi, 0.0), materials[materialIndex].shininess);"
"		resultColor += diffuse + specular;\n"
"	}\n"	
"	gl_FragColor = vec4(resultColor, 1.0) * texture(diffuseTex, ex_TexCoord);\n"
"}";

Shader3d::Shader3d() : Shader(ShaderInitType::Code, vertexShader, fragmentShader)
{}

void Shader3d::setModelMatrix(const glm::mat4x4& matrix)
{
	setUniform("model", matrix);
}

void Shader3d::setProjectionMatrix(const glm::mat4x4& matrix)
{
	setUniform("projection", matrix);
}

void Shader3d::setViewMatrix(const glm::mat4x4& matrix)
{
	setUniform("view", matrix);
}

void Shader3d::setNormalMatrix(const glm::mat4x4& matrix)
{
	setUniform("normalTm", matrix);
}

void Shader3d::setDiffuseTexture(Texture& texture)
{
	texture.bind(0);
}

void Shader3d::setMaterial(const Material& material, int index)
{
	std::string uniformPrefix = "materials[" + std::to_string(index) + "]";
	setUniform(uniformPrefix + ".emission", material.emission);
	setUniform(uniformPrefix + ".ambient", material.ambient);
	setUniform(uniformPrefix + ".diffuse", material.diffuse);
	setUniform(uniformPrefix + ".specular", material.specular);
	setUniform(uniformPrefix + ".shininess", material.shininess);
}

void Shader3d::setCurrentMaterialIndex(int index)
{
	setUniform("materialIndex", index);
}

void Shader3d::setEyeDirection(const glm::vec3& eyeDirection)
{
	setUniform("eyeDirection", eyeDirection);
}

void Shader3d::setDirectionalLightsCount(int count)
{
	setUniform("directionalLightsCount", count);
}

/*
"	vec3 ambientColor;\n"
"	vec3 diffuseColor;\n"
"	vec3 specularColor;\n"
*/

void Shader3d::setDirectionalLight(const DirectionalLight& light, int index)
{
	std::string uniformPrefix = "directionalLights[" + std::to_string(index) + "]";
	setUniform(uniformPrefix + ".direction", light.direction);
	setUniform(uniformPrefix + ".ambientColor", light.ambientColor);
	setUniform(uniformPrefix + ".diffuseColor", light.diffuseColor);
	setUniform(uniformPrefix + ".specularColor", light.specularColor);
}