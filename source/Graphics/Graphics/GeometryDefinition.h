#ifndef GRAPHICS_GEOMETRY_DEFINITION_H
#define GRAPHICS_GEOMETRY_DEFINITION_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include <cstdint>

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bitangent;
	glm::vec4 color;
	glm::vec2 texCoords;

	Vertex();
	Vertex(const glm::vec3& pos);
	Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec4& color, const glm::vec2& texCoords);
	Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec3& tangent, const glm::vec3& bitangent, const glm::vec4& color, const glm::vec2& texCoords);
};

enum class MeshType
{
	Triangles,
	Lines,
	Error
};

struct GeometryDefinition
{
	MeshType type;
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	
	GeometryDefinition(MeshType type);
	GeometryDefinition(MeshType type, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

	GeometryDefinition translate(const glm::vec3& translation);
	GeometryDefinition scale(const glm::vec3& scale);

	friend GeometryDefinition operator+(const GeometryDefinition& first, const GeometryDefinition& second);

	static GeometryDefinition XY_QUAD;
	static GeometryDefinition CUBE;
	static GeometryDefinition SCREEN;
	static GeometryDefinition LINE_X;
	static GeometryDefinition LINE_Y;

	static GeometryDefinition createSphere(int points);
	static GeometryDefinition createTorus(int points, float radius, float thickness);
	static GeometryDefinition createLine(const glm::vec3& p1, const glm::vec3& p2);
};

#endif