#include "TestSceneRenderer.h"
#include "Graphics/InputClient.h"

struct TestSceneRendererImpl
{
	std::shared_ptr<InputClient> inputClient;

	TestSceneRendererImpl();
};

TestSceneRendererImpl::TestSceneRendererImpl()
{
	inputClient = std::make_shared<InputClient>();
}

TestSceneRenderer::TestSceneRenderer(RenderTarget& renderTarget)
{
	data = std::make_shared<TestSceneRendererImpl>();
}

std::shared_ptr<InputClientBase> TestSceneRenderer::getInputClient()
{
	return data->inputClient;
}

void TestSceneRenderer::render(RenderTarget& renderTarget, float dt)
{
	//todo: implement
}

void TestSceneRenderer::renderUi(RenderTarget& renderTarget)
{
	//todo: implement
}