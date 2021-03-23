#ifndef TEST_SCENE_BLOOM
#define TEST_SCENE_BLOOM

#include "TestSceneBase.h"
#include <memory>

struct TestSceneBloomImpl;

struct TestSceneBloom : TestSceneBase
{
	TestSceneBloom(RenderTarget& renderTarget);
	void render(RenderTarget& renderTarget, float dt);
	void renderUi(RenderTarget& renderTarget);
private:
	std::shared_ptr<TestSceneBloomImpl> data;
};

#endif