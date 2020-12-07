#ifndef GRAPHICS_RENDER_OBJECT_H
#define GRAPHICS_RENDER_OBJECT_H

#include "Texture.h"
#include "GeometryDefinition.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

struct RenderObject
{
	Texture& texture;
	Mesh mesh;
	Transform transform;
	Material material;

	RenderObject(Texture& texture, const GeometryDefinition& geometryDefinition, const Material& material) :
		texture(texture),
		mesh(geometryDefinition),
		material(material)
	{}
};

#endif