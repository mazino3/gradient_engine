#include "TestSceneImGui.h"
#include "Graphics/InputClient.h"

struct TestSceneImGuiImpl
{
	std::shared_ptr<InputClient> inputClient;

	TestSceneImGuiImpl()
	{
		inputClient = std::make_shared<InputClient>();
	}
};

TestSceneImGui::TestSceneImGui()
{
	data = std::make_shared<TestSceneImGuiImpl>();
}

std::shared_ptr<InputClientBase> TestSceneImGui::getInputClient()
{
	return data->inputClient;
}

void TestSceneImGui::render(RenderTarget& renderTarget, float dt)
{
	//todo: implement
}

void TestSceneImGui::renderUi()
{
	//todo: implement
}