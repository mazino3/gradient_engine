#include <gtest/gtest.h>

#include "RayAABBIntersectionTest.h"
#include "UndoManagerTest.h"

TEST(TestGroup, SimpleTest)
{
	EXPECT_EQ(true, true);
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}