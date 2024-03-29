#ifndef GRAPHICS_SKYBOX_OBJECT_H
#define GRAPHICS_SKYBOX_OBJECT_H

#include <Graphics/Mesh.h>
#include <Graphics/Transform.h>
#include <Graphics/CubeMap.h>
#include <Graphics/GeometryDefinition.h>
#include <glm/vec3.hpp>

struct SkyboxObject
{
	Mesh mesh;
	Transform transform;
	CubeMap& cubemap;

	SkyboxObject(CubeMap& cubemap) :
		mesh(GeometryDefinition::CUBE),
		cubemap(cubemap)
	{
		transform.position = glm::vec3(0, 0, 0);
		transform.scale = glm::vec3(2, 2, 2);
		transform.rotation = glm::vec3(90, 0, 0);
	}
};

#endif