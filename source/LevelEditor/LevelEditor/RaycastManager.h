#ifndef RAYCAST_MANAGER_H
#define RAYCAST_MANAGER_H

#include <memory>
#include <Math/Geometry/AABB.h>
#include <Math/Geometry/Ray.h>
#include <functional>

struct RaycastManagerImpl;

struct RaycastManager
{
	RaycastManager();
	~RaycastManager();

	void registerAABB(AABB& aabb, std::function<void(void)> onRaycast);
	void unregisterAABB(AABB& aabb);
	bool raycast(const Ray& ray);

private:
	std::unique_ptr<RaycastManagerImpl> data;
};

#endif