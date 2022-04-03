#ifndef LEVEL_OBJECT_H
#define LEVEL_OBJECT_H

#include <memory>
#include <Graphics/Renderer.h>
#include <Math/Geometry/AABB.h>
#include <glm/vec3.hpp>
#include "Resources.h"
#include "LevelData.h"

struct LevelObjectImpl;

struct LevelObject
{
	LevelObject(Renderer& renderer, Resources& resources, glm::vec3 pos, glm::vec3 scale);
	~LevelObject();

	void setPosition(const glm::vec3& pos);
	glm::vec3 getPosition();

	void setScale(const glm::vec3& scale);
	glm::vec3 getScale();

	AABB& getAABB();
	LevelDataObject toDataObject();

	void update();

private:
	std::unique_ptr<LevelObjectImpl> data;
};

#endif