#ifndef RAY_AABB_INTERSECTION_TEST
#define RAY_AABB_INTERSECTION_TEST

#include <gtest/gtest.h>
#include <Math/Geometry/AABB.h>

TEST(Geometry, RayAABBIntersection)
{
	AABB aabb(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	Ray ray;

	//tracing ray from all sides into the box

	ray.origin = glm::vec3(-1, 0, 0);
	ray.direction = glm::vec3(1, 0, 0);
	ASSERT_TRUE(aabb.intersectsWith(ray));

	ray.origin = glm::vec3(1, 0, 0);
	ray.direction = glm::vec3(-1, 0, 0);
	ASSERT_TRUE(aabb.intersectsWith(ray));

	ray.origin = glm::vec3(0, 1, 0);
	ray.direction = glm::vec3(0, -1, 0);
	ASSERT_TRUE(aabb.intersectsWith(ray));

	ray.origin = glm::vec3(0, -1, 0);
	ray.direction = glm::vec3(0, 1, 0);
	ASSERT_TRUE(aabb.intersectsWith(ray));

	ray.origin = glm::vec3(0, 0, 1);
	ray.direction = glm::vec3(0, 0, -1);
	ASSERT_TRUE(aabb.intersectsWith(ray));

	ray.origin = glm::vec3(0, 0, -1);
	ray.direction = glm::vec3(0, 0, 1);
	ASSERT_TRUE(aabb.intersectsWith(ray));

	//tracing ray in the opposite direction

	ray.origin = glm::vec3(0, 0, 2);
	ray.direction = glm::vec3(0, 0, 2);
	ASSERT_FALSE(aabb.intersectsWith(ray));
}

#endif