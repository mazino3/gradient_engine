#include "RaycastManager.h"
#include <vector>
#include <utility>
#include <glm/ext.hpp>

struct RaycastManagerElement
{
	AABB* aabb;
	std::function<void(void)> callback;

	RaycastManagerElement(AABB& aabb, std::function<void(void)> callback) :
		aabb(&aabb),
		callback(callback)
	{}

	RaycastManagerElement() {}
};

struct RaycastManagerImpl
{
	std::vector<RaycastManagerElement> elements;
};

RaycastManager::RaycastManager()
{
	data = std::make_unique<RaycastManagerImpl>();
}

RaycastManager::~RaycastManager()
{
}

void RaycastManager::registerAABB(AABB& aabb, std::function<void(void)> onRaycast)
{
	data->elements.push_back(RaycastManagerElement(aabb, onRaycast));
}

void RaycastManager::unregisterAABB(AABB& aabb)
{
	int index = -1;
	for (int i = 0; i < data->elements.size(); i++)
	{
		if (data->elements[i].aabb == &aabb)
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		std::swap(data->elements.back(), data->elements[index]);
		data->elements.pop_back();
	}
}

bool RaycastManager::raycast(const Ray& ray)
{
	RaycastManagerElement closest;
	bool firstElementFound = false;
	float minDistance;

	for (auto& element : data->elements)
	{
			glm::vec3 p1;
			glm::vec3 p2;
			if (element.aabb->intersectsWith(ray, p1, p2))
			{
				float currentDistance = std::min(glm::distance(p1, ray.origin), glm::distance(p2, ray.origin));
				if (!firstElementFound || currentDistance < minDistance)
				{
					firstElementFound = true;
					minDistance = currentDistance;
					closest = element;
				}
			}
	}
	if (firstElementFound)
	{
		closest.callback();
	}
	return firstElementFound;
}

