#ifndef GRAPHICS_TEST_TEST_SCENE_RENDERER
#define GRAPHICS_TEST_TEST_SCENE_RENDERER

#include "Graphics/RenderTarget.h"
#include "TestSceneBase.h"
#include <memory>

struct TestSceneRendererImpl;

struct TestSceneRenderer : TestSceneBase
{
	TestSceneRenderer(RenderTarget& renderTarget);
	InputClientBase& getInputClient() override;
	void render(RenderTarget& renderTarget, float dt) override;
	void renderUi(RenderTarget& renderTarget) override;
private:
	std::shared_ptr<TestSceneRendererImpl> data;
};

#endif