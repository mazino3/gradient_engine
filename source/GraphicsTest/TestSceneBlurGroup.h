#ifndef GRAPHICS_TEST_BLUR_GROUP_H
#define GRAPHICS_TEST_BLUR_GROUP_H

#include "TestSceneBase.h"
#include <memory>

struct TestSceneBlurGroupImpl;

struct TestSceneBlurGroup : TestSceneBase
{
	TestSceneBlurGroup(RenderTarget& renderTarget);
	void render(RenderTarget& renderTarget, float dt);
	void renderUi(RenderTarget& renderTarget);
private:
	std::shared_ptr<TestSceneBlurGroupImpl> data;
};

#endif