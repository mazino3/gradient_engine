#include "Scene.h"
#include "LevelObject.h"
#include <vector>

struct SceneImpl
{
	Renderer& renderer;
	Resources& resources;
	SelectionManager& selectionManager;
	RaycastManager& raycastManager;

	std::vector<std::shared_ptr<LevelObject>> objects;

	SceneImpl(Renderer& renderer, Resources& resources, SelectionManager& selectionManager, RaycastManager& raycastManager);
};

SceneImpl::SceneImpl(Renderer& renderer, Resources& resources, SelectionManager& selectionManager, RaycastManager& raycastManager) :
	renderer(renderer),
	resources(resources),
	selectionManager(selectionManager),
	raycastManager(raycastManager)
{
}

Scene::Scene(Renderer& renderer, Resources& resources, SelectionManager& selectionManager, RaycastManager& raycastManager)
{
	data = std::make_unique<SceneImpl>(renderer, resources, selectionManager, raycastManager);
}

Scene::~Scene()
{
}

void Scene::load(const LevelData& levelData)
{
	for (auto& obj : levelData.objects)
	{
		auto newObject = std::make_shared<LevelObject>(data->renderer, data->resources, data->selectionManager, data->raycastManager, obj.position, obj.scale);
		data->objects.push_back(newObject);
	}
}

LevelData Scene::getLevelData()
{
	LevelData result;
	for (auto& obj : data->objects)
	{
		result.objects.push_back(LevelDataObject(obj->getPosition(), obj->getScale()));
	}
	return result;
}

void Scene::update()
{
	//todo: implement
}