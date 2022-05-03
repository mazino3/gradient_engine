#include "Scene.h"
#include "LevelObject.h"
#include "DepSupplier.h"
#include <vector>

struct SceneImpl
{
	DepSupplier& depSupplier;
	std::vector<std::shared_ptr<LevelObject>> objects;

	SceneImpl(DepSupplier& depSupplier) :
		depSupplier(depSupplier)
	{}
};


Scene::Scene(DepSupplier& depSupplier)
{
	data = std::make_unique<SceneImpl>(depSupplier);
}

Scene::~Scene()
{
}

void Scene::load(const LevelData& levelData)
{
	for (auto& obj : levelData.objects)
	{
		auto newObject = std::make_shared<LevelObject>(data->depSupplier, obj.position, obj.scale);
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