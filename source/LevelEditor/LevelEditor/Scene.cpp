#include "Scene.h"

struct SceneImpl
{
	Renderer& renderer;
	Resources& resources;

	SceneImpl(Renderer& renderer, Resources& resources);
};

SceneImpl::SceneImpl(Renderer& renderer, Resources& resources) :
	renderer(renderer),
	resources(resources)
{
}

Scene::Scene(Renderer& renderer, Resources& resources)
{
	data = std::make_unique<SceneImpl>(renderer, resources);
}

Scene::~Scene()
{
}

void Scene::load(const LevelData& levelData)
{
	//todo: implement
}

LevelData Scene::getLevelData()
{
	//todo: implement
}

void Scene::update()
{
	//todo: implement
}