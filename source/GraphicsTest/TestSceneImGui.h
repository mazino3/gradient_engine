#ifndef GRAPHICS_TEST_TEST_SCENE_IMGUI_H
#define GRAPHICS_TEST_TEST_SCENE_IMGUI_H

#include "TestSceneBase.h"
#include <memory>

struct TestSceneImGuiImpl;

struct TestSceneImGui : TestSceneBase
{
	TestSceneImGui();
	InputClientBase& getInputClient() override;
	void render(RenderTarget& renderTarget, float dt) override;
	void renderUi() override;
private:
	std::shared_ptr<TestSceneImGuiImpl> data;
};

#endif