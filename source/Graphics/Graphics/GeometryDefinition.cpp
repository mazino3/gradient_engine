#include <Graphics/GeometryDefinition.h>
#include <Graphics/Colors.h>
#include <glm/ext.hpp>

static const float PI = 3.141593f;

using namespace glm;

Vertex::Vertex() : 
	pos(0, 0, 0),
	normal(0, 0, 0),
	tangent(0, 0, 0),
	bitangent(0, 0, 0),
	color(1, 1, 1, 1),
	texCoords(0, 0)
{}

Vertex::Vertex(const vec3& pos) :
	pos(pos),
	normal(0, 0, 0),
	tangent(0, 0, 0),
	bitangent(0, 0, 0),
	color(0, 0, 0, 0),
	texCoords(0, 0)
{}

Vertex::Vertex(const vec3& pos, const vec3& normal, const vec4& color, const vec2& texCoords) :
	pos(pos),
	normal(normal),
	tangent(0, 0, 0),
	bitangent(0, 0, 0),
	color(color),
	texCoords(texCoords)
{}

Vertex::Vertex(const vec3& pos, const vec3& normal, const vec3& tangent, const vec3& bitangent, const vec4& color, const vec2& texCoords) :
	pos(pos),
	normal(normal),
	tangent(tangent),
	bitangent(bitangent),
	color(color),
	texCoords(texCoords)
{}

GeometryDefinition::GeometryDefinition(MeshType type) :
	type(type)
{}

GeometryDefinition::GeometryDefinition(MeshType type, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) :
	vertices(vertices),
	indices(indices),
	type(type)
{}

GeometryDefinition operator+(const GeometryDefinition& first, const GeometryDefinition& second)
{
	if (first.type != second.type)
	{
		return GeometryDefinition(MeshType::Error);
	}
	
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	for (auto& vertex : first.vertices)
	{
		vertices.push_back(vertex);
	}

	for (auto& index : first.indices)
	{
		indices.push_back(index);
	}
	
	for (auto& vertex : second.vertices)
	{
		vertices.push_back(vertex);
	}

	for (auto& index : second.indices)
	{
		indices.push_back(index + first.indices.size());
	}

	return GeometryDefinition(first.type, vertices, indices);
}

GeometryDefinition GeometryDefinition::translate(const glm::vec3& translation)
{
	std::vector<Vertex> newVertices;

	for (auto& vertex : vertices)
	{
		newVertices.push_back(vertex);
		newVertices.back().pos += translation;
	}

	return GeometryDefinition(type, newVertices, indices);
}

GeometryDefinition GeometryDefinition::scale(const glm::vec3& scale)
{
	std::vector<Vertex> newVertices;

	for (auto& vertex : vertices)
	{
		newVertices.push_back(vertex);
		newVertices.back().pos *= scale;
	}

	return GeometryDefinition(type, newVertices, indices);
}


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

GeometryDefinition GeometryDefinition::LINE_X(
	MeshType::Lines,
	std::vector<Vertex>
	{
		Vertex(vec3(0, 0, 0), vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0), Colors::WHITE, vec2(0, 0)),
		Vertex(vec3(1, 0, 0), vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0), Colors::WHITE, vec2(1, 1))
	},
	std::vector<uint32_t>
	{
		0, 1
	}
);
GeometryDefinition GeometryDefinition::LINE_Y(
	MeshType::Lines,
	std::vector<Vertex>
	{
		Vertex(vec3(0, 0, 0), vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0), Colors::WHITE, vec2(0, 0)),
		Vertex(vec3(0, 1, 0), vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0), Colors::WHITE, vec2(1, 1))
	},
	std::vector<uint32_t>
	{
		0, 1
	}
);

GeometryDefinition GeometryDefinition::SCREEN(
	MeshType::Triangles,
	std::vector<Vertex>
	{
		Vertex(vec3(-1, -1, 0), vec3(), vec4(), vec2(0, 0)),
		Vertex(vec3(1, -1, 0), vec3(), vec4(), vec2(1, 0)),
		Vertex(vec3(1, 1, 0), vec3(), vec4(), vec2(1, 1)),
		Vertex(vec3(-1, 1, 0), vec3(), vec4(), vec2(0, 1))
	},
	std::vector<uint32_t>
	{
		0, 1, 2,
		0, 2, 3
	}
);

GeometryDefinition GeometryDefinition::CUBE(
	MeshType::Triangles,
	std::vector<Vertex>
	{
	//xy quads
		Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(0, 0, -1), vec3(-1, 0, 0), vec3(0, -1, 0), Colors::WHITE, vec2(0, 0)),
		Vertex(vec3(0.5f, -0.5f, -0.5f), vec3(0, 0, -1), vec3(-1, 0, 0), vec3(0, -1, 0), Colors::WHITE, vec2(1, 0)),
		Vertex(vec3(0.5f, 0.5f, -0.5f), vec3(0, 0, -1), vec3(-1, 0, 0), vec3(0, -1, 0), Colors::WHITE, vec2(1, 1)),
		Vertex(vec3(-0.5f, 0.5f, -0.5f), vec3(0, 0, -1), vec3(-1, 0, 0), vec3(0, -1, 0), Colors::WHITE, vec2(0, 1)),

		Vertex(vec3(-0.5f, -0.5f, 0.5f), vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0), Colors::WHITE, vec2(0, 0)),
		Vertex(vec3(0.5f, -0.5f, 0.5f), vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0), Colors::WHITE, vec2(1, 0)),
		Vertex(vec3(0.5f, 0.5f, 0.5f), vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0), Colors::WHITE, vec2(1, 1)),
		Vertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0), Colors::WHITE, vec2(0, 1)),
	//xz quads
		Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(0, -1, 0), vec3(-1, 0, 0), vec3(0, 0, -1), Colors::WHITE, vec2(0, 0)),
		Vertex(vec3(0.5f, -0.5f, -0.5f), vec3(0, -1, 0), vec3(-1, 0, 0), vec3(0, 0, -1), Colors::WHITE, vec2(1, 0)),
		Vertex(vec3(0.5f, -0.5f, 0.5f), vec3(0, -1, 0), vec3(-1, 0, 0), vec3(0, 0, -1), Colors::WHITE, vec2(1, 1)),
		Vertex(vec3(-0.5f, -0.5f, 0.5f), vec3(0, -1, 0), vec3(-1, 0, 0), vec3(0, 0, -1), Colors::WHITE, vec2(0, 1)),

		Vertex(vec3(-0.5f, 0.5f, -0.5f), vec3(0, 1, 0), vec3(1, 0, 0), vec3(0, 0, 1), Colors::WHITE, vec2(0, 0)),
		Vertex(vec3(0.5f, 0.5f, -0.5f), vec3(0, 1, 0), vec3(1, 0, 0), vec3(0, 0, 1), Colors::WHITE, vec2(1, 0)),
		Vertex(vec3(0.5f, 0.5f, 0.5f), vec3(0, 1, 0), vec3(1, 0, 0), vec3(0, 0, 1), Colors::WHITE, vec2(1, 1)),
		Vertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0, 1, 0), vec3(1, 0, 0), vec3(0, 0, 1), Colors::WHITE, vec2(0, 1)),
	//yz quads
		Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(-1, 0, 0), vec3(0, -1, 0), vec3(0, 0, -1), Colors::WHITE, vec2(0, 0)),
		Vertex(vec3(-0.5f, 0.5f, -0.5f), vec3(-1, 0, 0), vec3(0, -1, 0), vec3(0, 0, -1), Colors::WHITE, vec2(1, 0)),
		Vertex(vec3(-0.5f, 0.5f, 0.5f), vec3(-1, 0, 0), vec3(0, -1, 0), vec3(0, 0, -1), Colors::WHITE, vec2(1, 1)),
		Vertex(vec3(-0.5f, -0.5f, 0.5f), vec3(-1, 0, 0), vec3(0, -1, 0), vec3(0, 0, -1), Colors::WHITE, vec2(0, 1)),

		Vertex(vec3(0.5f, -0.5f, -0.5f), vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1), Colors::WHITE, vec2(0, 0)),
		Vertex(vec3(0.5f, 0.5f, -0.5f), vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1), Colors::WHITE, vec2(1, 0)),
		Vertex(vec3(0.5f, 0.5f, 0.5f), vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1), Colors::WHITE, vec2(1, 1)),
		Vertex(vec3(0.5f, -0.5f, 0.5f), vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1), Colors::WHITE, vec2(0, 1)),
	},
	std::vector<uint32_t> //schet drevnih schizov
	{
		0, 1, 2,
		0, 2, 3,

		4, 5, 6,
		4, 6, 7,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23
	}
);

GeometryDefinition GeometryDefinition::createSphere(int points)
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	//adding vertices

	for (int i = 0; i <= points; i++)
	{
		for (int j = 0; j <= points; j++)
		{
			float texCoordX = (float)j / (float)points;
			float texCoordY = (float)i / (float)points;
			float angleA = (float)i / (float)points * PI;
			float angleB = (float)j / (float)points * PI * 2;
			float r = sinf(angleA);
			float x = cosf(angleB) * r;
			float y = sinf(angleB) * r;
			float z = cosf(angleA);
			
			vertices.push_back(Vertex(glm::vec3(x, y, z), glm::vec3(x, y, z), Colors::WHITE, glm::vec2(texCoordX, texCoordY)));
		}
	}

	//adding indices

	for (int i = 0; i < points; i++)
	{
		for (int j = 0; j < points; j++)
		{
			indices.push_back(j + i * (points + 1));
			indices.push_back(j + 1 + i * (points + 1));
			indices.push_back(j + 1 + (i + 1) * (points + 1));

			indices.push_back(j + i * (points + 1));
			indices.push_back(j + 1 + (i + 1) * (points + 1));
			indices.push_back(j + (i + 1) * (points + 1));
		}
	}

	return GeometryDefinition(MeshType::Triangles, vertices, indices);
}

GeometryDefinition GeometryDefinition::createTorus(int points, float radius, float thickness)
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	for (int i = 0; i <= points; i++)
	{
		float phase = (float)i / (float)(points) * PI * 2;
		for (int j = 0; j <= points; j++)
		{
			float phase2 = (float)j / (float)points * PI * 2;
			glm::vec4 origin(radius, 0, 0, 1);
			glm::vec4 normal(cosf(phase2), 0, sinf(phase2), 1);
			float tangentPhase = phase2 - PI / 2;
			glm::vec4 tangent(cosf(tangentPhase), 0, sinf(tangentPhase), 1);
			glm::vec4 bitangent(0, 1, 0, 1);
			glm::vec4 pos = origin + normal * thickness;
			glm::vec2 texCoord(phase / PI / 2, phase2 / PI / 2);

			glm::mat4x4 rotMatrix = glm::rotate(glm::mat4x4(1.0f), phase, glm::vec3(0.0f, 0.0f, 1.0f));
			normal = rotMatrix * normal;
			tangent = rotMatrix * tangent;
			bitangent = rotMatrix * bitangent;
			pos = rotMatrix * pos;

			vertices.push_back(Vertex(pos, normal, tangent, bitangent, Colors::WHITE, texCoord));
		}
	}

	for (int i = 0; i < points; i++)
	{
		for (int j = 0; j < points; j++)
		{
			indices.push_back(j + i * (points + 1));
			indices.push_back(j + 1 + i * (points + 1));
			indices.push_back(j + 1 + (i + 1) * (points + 1));

			indices.push_back(j + i * (points + 1));
			indices.push_back(j + 1 + (i + 1) * (points + 1));
			indices.push_back(j + (i + 1) * (points + 1));
		}
	}

	return GeometryDefinition(MeshType::Triangles, vertices, indices);
}

