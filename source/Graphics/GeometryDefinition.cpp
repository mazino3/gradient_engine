#include "GeometryDefinition.h"
#include "Colors.h"

using namespace glm;

Vertex::Vertex() : 
	pos(0, 0, 0),
	normal(0, 0, 0),
	color(1, 1, 1, 1),
	texCoords(0, 0)
{}

Vertex::Vertex(const vec3& pos, const vec3& normal, const vec4& color, const vec2& texCoords) :
	pos(pos),
	normal(normal),
	color(color),
	texCoords(texCoords)
{}

GeometryDefinition::GeometryDefinition(MeshType type, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) :
	vertices(vertices),
	indices(indices),
	type(type)
{}

GeometryDefinition GeometryDefinition::XY_QUAD(
	MeshType::Triangles,
	std::vector<Vertex>
	{
		Vertex(vec3(-0.5f, -0.5f, 0), vec3(0, 0, -1), Colors::WHITE, vec2(0, 0)),
		Vertex(vec3(0.5f, -0.5f, 0), vec3(0, 0, -1), Colors::WHITE, vec2(1, 0)),
		Vertex(vec3(0.5f, 0.5f, 0), vec3(0, 0, -1), Colors::WHITE, vec2(1, 1)),
		Vertex(vec3(-0.5f, 0.5f, 0), vec3(0, 0, -1), Colors::WHITE, vec2(0, 1)),
	}, 
	std::vector<uint32_t> 
	{
		0, 1, 2,
		0, 2, 3
	}
);