#ifndef LEVEL_OBJECT_H
#define LEVEL_OBJECT_H

#include <memory>
#include <Graphics/Renderer.h>
#include <glm/vec3.hpp>

struct LevelObjectImpl;

struct LevelObject
{
	LevelObject(Renderer& renderer, glm::vec3 pos, glm::vec3 scale);
	~LevelObject();

private:
	std::unique_ptr<LevelObjectImpl> data;
};

#endif