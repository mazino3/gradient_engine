#include "Mesh.h"
#include <GL/glew.h>

struct MeshImpl
{
	int indicesCount;
	MeshType meshType;
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
};

Mesh::Mesh(const GeometryDefinition& geometry)
{
	_data = std::make_shared<MeshImpl>();
	_data->meshType = geometry.type;
	_data->indicesCount = geometry.indices.size();

	//creating vao
	glGenVertexArrays(1, &_data->vao);
	glBindVertexArray(_data->vao);
	
	//creating vbo
	glGenBuffers(1, &_data->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _data->vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(Vertex) * geometry.vertices.size(),
		&geometry.vertices[0],
		GL_STATIC_DRAW);

	//pos attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Vertex::pos));

	//color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Vertex::color));

	//creating ebo
	glGenBuffers(1, &_data->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _data->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * geometry.indices.size(), &geometry.indices[0], GL_STATIC_DRAW);

	//unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	//todo: implement
}

void Mesh::draw()
{
	int glPrimitiveType = GL_TRIANGLES;
	switch (_data->meshType)
	{
		case MeshType::Triangles:
			glPrimitiveType = GL_TRIANGLES;
	}

	glBindVertexArray(_data->vao);
	glDrawElements(glPrimitiveType, _data->indicesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}