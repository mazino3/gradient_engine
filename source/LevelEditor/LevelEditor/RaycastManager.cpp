#include "RaycastManager.h"

struct RaycastManagerImpl
{

};

RaycastManager::RaycastManager()
{
	data = std::make_unique<RaycastManagerImpl>();
}

RaycastManager::~RaycastManager()
{
	//todo: implement
}

void RaycastManager::registerAABB(AABB& aabb, std::function<void(void)> onRaycast)
{
	//todo: implement
}

void RaycastManager::unregisterAABB(AABB& aabb)
{
	//todo: implement
}

void RaycastManager::raycast(const Ray& ray)
{
	//todo: implement
}

