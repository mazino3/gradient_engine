#ifndef GRAPHICS_TEST_TEST_SCENE_BASE_H
#define GRAPHICS_TEST_TEST_SCENE_BASE_H

#include "Graphics/InputClientBase.h"
#include "Graphics/RenderTarget.h"
#include <memory>
#include <functional>
#include <vector>

struct TestSceneBaseImpl;

struct TestSceneBase
{
	TestSceneBase();

	virtual ~TestSceneBase();
	virtual std::vector<InputClientBase*> getInputClients();
	virtual void render(RenderTarget& renderTarget, float dt) = 0;
	virtual void renderUi(RenderTarget& renderTarget) = 0;

	void onDestroy(std::function<void(void)> callback);
private:
	std::shared_ptr<TestSceneBaseImpl> data;
};

#endif