#include "TestSceneImGui.h"
#include "Graphics/InputClient.h"

struct TestSceneImGuiImpl
{
	InputClient inputClient;
};

TestSceneImGui::TestSceneImGui()
{
	data = std::make_shared<TestSceneImGuiImpl>();
}

InputClientBase& TestSceneImGui::getInputClient()
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