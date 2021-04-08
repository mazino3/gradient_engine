#ifndef RAY_AABB_INTERSECTION_TEST
#define RAY_AABB_INTERSECTION_TEST

#include <gtest/gtest.h>
#include <Math/Geometry/AABB.h>
#include <glm/ext.hpp>

TEST(Geometry, RayAABBIntersection)
{
	AABB aabb(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	Ray ray;

	//tracing ray from all sides into the box

	ray.origin = glm::vec3(-1, 0, 0);
	ray.direction = glm::vec3(1, 0, 0);
	EXPECT_TRUE(aabb.intersectsWith(ray));

	ray.origin = glm::vec3(1, 0, 0);
	ray.direction = glm::vec3(-1, 0, 0);
	EXPECT_TRUE(aabb.intersectsWith(ray));

	ray.origin = glm::vec3(0, 1, 0);
	ray.direction = glm::vec3(0, -1, 0);
	EXPECT_TRUE(aabb.intersectsWith(ray));

	ray.origin = glm::vec3(0, -1, 0);
	ray.direction = glm::vec3(0, 1, 0);
	EXPECT_TRUE(aabb.intersectsWith(ray));

	ray.origin = glm::vec3(0, 0, 1);
	ray.direction = glm::vec3(0, 0, -1);
	EXPECT_TRUE(aabb.intersectsWith(ray));

	ray.origin = glm::vec3(0, 0, -1);
	ray.direction = glm::vec3(0, 0, 1);
	EXPECT_TRUE(aabb.intersectsWith(ray));

	//checking collision points

	ray.origin = glm::vec3(1, 0, 0);
	ray.direction = glm::vec3(-1, 0, 0);
	glm::vec3 p1;
	glm::vec3 p2;
	aabb.intersectsWith(ray, p1, p2);

	static float eps = 0.0001f;

	EXPECT_NEAR(p1.x, -0.5f, eps);
	EXPECT_NEAR(p1.y, 0.0f, eps);
	EXPECT_NEAR(p1.z, 0.0f, eps);

	EXPECT_NEAR(p2.x, 0.5f, eps);
	EXPECT_NEAR(p2.y, 0.0f, eps);
	EXPECT_NEAR(p2.z, 0.0f, eps);

	//tracing ray in the opposite direction

	ray.origin = glm::vec3(0, 0, 2);
	ray.direction = glm::vec3(0, 0, 2);
	EXPECT_FALSE(aabb.intersectsWith(ray));

	//tracing ray diagonally

	ray.origin = glm::vec3(2, 2, 2);
	ray.direction = glm::normalize(glm::vec3(-1, -1, -1));
	
	p1.x = 1337;
	EXPECT_TRUE(aabb.intersectsWith(ray, p1, p2));

	//EXPECT_NEAR(p1.x, 0.5f, eps);
	//EXPECT_NEAR(p1.y, 0.5f, eps);
	//EXPECT_NEAR(p1.z, 0.5f, eps);
}

#endif