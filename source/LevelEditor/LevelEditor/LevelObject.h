#ifndef LEVEL_OBJECT_H
#define LEVEL_OBJECT_H

#include <memory>
#include <Graphics/Renderer.h>
#include <Math/Geometry/AABB.h>
#include <glm/vec3.hpp>
#include "Resources.h"

struct LevelObjectImpl;

struct LevelObject
{
	LevelObject(Renderer& renderer, Resources& resources, glm::vec3 pos, glm::vec3 scale);
	~LevelObject();

	void setPosition(const glm::vec3& pos);
	glm::vec3 getPosition();

	AABB& getAABB();

	void update();

private:
	std::unique_ptr<LevelObjectImpl> data;
};

#endif