#ifndef GRAPHICS_TEST_TEST_SCENE_BASE_H
#define GRAPHICS_TEST_TEST_SCENE_BASE_H

#include "Graphics/InputClientBase.h"
#include "Graphics/RenderTarget.h"

struct TestSceneBase
{
	virtual ~TestSceneBase() {}
	virtual InputClientBase& getInputClient() = 0;
	virtual void render(RenderTarget& renderTarget, float dt) = 0;
	virtual void renderUi() = 0;
};

#endif