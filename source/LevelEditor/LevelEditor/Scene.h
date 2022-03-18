#ifndef LEVEL_EDITOR_SCENE_H
#define LEVEL_EDITOR_SCENE_H

#include <memory>
#include "LevelData.h"
#include "Resources.h"
#include <Graphics/Renderer.h>

struct SceneImpl;

struct Scene
{
	Scene(Renderer& renderer, Resources& resouces);
	~Scene();

	void load(const LevelData& levelData);
	LevelData getLevelData();

	void update();

private:
	std::unique_ptr<SceneImpl> data;
};

#endif