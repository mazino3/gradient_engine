#ifndef GRAPHICS_TEST_TEST_SCENE_BASE_H
#define GRAPHICS_TEST_TEST_SCENE_BASE_H

#include "Graphics/InputClientBase.h"
#include "Graphics/RenderTarget.h"
#include <memory>
#include <functional>

struct TestSceneBaseImpl;

struct TestSceneBase
{
	TestSceneBase();

	virtual ~TestSceneBase();
	virtual std::shared_ptr<InputClientBase> getInputClient() = 0;
	virtual void render(RenderTarget& renderTarget, float dt) = 0;
	virtual void renderUi() = 0;

	void onDestroy(std::function<void(void)> callback);
private:
	std::shared_ptr<TestSceneBaseImpl> data;
};

#endif