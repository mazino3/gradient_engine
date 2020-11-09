#ifndef GRAPHICS_MESH_H
#define GRAPHICS_MESH_H

#include "GeometryDefinition.h"
#include <memory>

struct MeshImpl;

struct Mesh
{
	Mesh(const GeometryDefinition& geometry);
	~Mesh();
	void draw();

private:

	std::shared_ptr<MeshImpl> _data;
};

#endif