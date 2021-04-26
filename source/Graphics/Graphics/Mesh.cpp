#include <Graphics/Mesh.h>
#include <GL/glew.h>

struct MeshImpl
{
	GeometryDefinition geometry;
	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	MeshImpl(const GeometryDefinition& geometry) :
	    geometry(geometry),
		vao(0),
		vbo(0),
		ebo(0)
    {}
};

Mesh::Mesh(const GeometryDefinition& geometry)
{
	_data = std::make_shared<MeshImpl>(geometry);

	//creating vao
	glGenVertexArrays(1, &_data->vao);
	glBindVertexArray(_data->vao);
	
	//creating vbo
	glGenBuffers(1, &_data->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _data->vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(Vertex) * _data->geometry.vertices.size(),
		&_data->geometry.vertices[0],
		GL_STATIC_DRAW);

	//pos attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Vertex::pos));

	//color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Vertex::color));

	//texCoord attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Vertex::texCoords));

	//normal attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Vertex::normal));

	//tangent attribute
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::tangent));

	//bitangent attribute
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::bitangent));

	//creating ebo
	glGenBuffers(1, &_data->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _data->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _data->geometry.indices.size(), &_data->geometry.indices[0], GL_STATIC_DRAW);

	//unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &_data->ebo);
	glDeleteBuffers(1, &_data->vbo);
	glDeleteVertexArrays(1, &_data->vao);
}

void Mesh::draw() const
{
	int glPrimitiveType = GL_TRIANGLES;
	switch (_data->geometry.type)
	{
		case MeshType::Triangles:
			glPrimitiveType = GL_TRIANGLES;
			break;
		case MeshType::Lines:
			glPrimitiveType = GL_LINES;
			break;
	}

	glBindVertexArray(_data->vao);
	glDrawElements(glPrimitiveType, _data->geometry.indices.size(), GL_UNSIGNED_INT, &_data->geometry.indices[0]);
	glBindVertexArray(0);
}