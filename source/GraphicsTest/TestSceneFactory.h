#ifndef GRAPHICS_TEST_TEST_SCENE_FACTORY_H
#define GRAPHICS_TEST_TEST_SCENE_FACTORY_H

#include <vector>
#include <string>
#include <memory>
#include "TestSceneBase.h"
#include "Graphics/RenderTarget.h"

typedef int TestSceneId;

struct TestSceneFactory
{
	static std::vector<TestSceneId> getSceneIds();
	static std::string getSceneName(TestSceneId id);
	static std::shared_ptr<TestSceneBase> createScene(TestSceneId id, RenderTarget& renderTarget);
};

#endif