#ifndef GRAPHICS_MESH_H
#define GRAPHICS_MESH_H

#include <Graphics/GeometryDefinition.h>
#include <memory>

struct MeshImpl;

struct Mesh
{
	Mesh(const GeometryDefinition& geometry);
	~Mesh();
	void draw() const;

private:

	std::shared_ptr<MeshImpl> _data;
};

#endif