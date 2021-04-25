#ifndef TEST_SCENE_LINE
#define TEST_SCENE_LINE

#include "TestSceneBase.h"
#include <memory>

struct TestSceneLineImpl;

struct TestSceneLine : TestSceneBase
{
	TestSceneLine(RenderTarget& renderTarget);
	void render(RenderTarget& renderTarget, float dt);
	void renderUi(RenderTarget& renderTarget);
private:
	std::unique_ptr<TestSceneLineImpl> data;
};

#endif