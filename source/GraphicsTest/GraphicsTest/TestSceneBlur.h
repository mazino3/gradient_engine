#ifndef TEST_SCENE_BLUR
#define TEST_SCENE_BLUR

#include "TestSceneBase.h"
#include <memory>

struct TestSceneBlurImpl;

struct TestSceneBlur : TestSceneBase
{
	TestSceneBlur(RenderTarget& renderTarget);
	void render(RenderTarget& renderTarget, float dt);
	void renderUi(RenderTarget& renderTarget);
private:
	std::shared_ptr<TestSceneBlurImpl> data;
};

#endif