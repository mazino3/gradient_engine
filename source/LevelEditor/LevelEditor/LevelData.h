#ifndef LEVEL_DATA_H
#define LEVEL_DATA_H

#include <glm/glm.hpp>
#include <vector>

struct LevelDataObject
{
	glm::vec3 position;
	glm::vec3 scale;

	LevelDataObject() :
		position(0, 0, 0),
		scale(0, 0, 0)
	{}

	LevelDataObject(const glm::vec3& position, const glm::vec3& scale) :
		position(position),
		scale(scale)
	{}
};

struct LevelData
{
	std::vector<LevelDataObject> objects;
};

#endif