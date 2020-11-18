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
	glm::vec4 color;
	glm::vec2 texCoords;

	Vertex();
	Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec4& color, const glm::vec2& texCoords);
};

enum class MeshType
{
	Triangles
};

struct GeometryDefinition
{
	const MeshType type;
	const std::vector<Vertex> vertices;
	const std::vector<uint32_t> indices;

	GeometryDefinition(MeshType type, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

	static GeometryDefinition XY_QUAD;
	static GeometryDefinition CUBE;
};

#endif