#include "TestSceneImGui.h"
#include "Graphics/InputClient.h"
#include "imgui.h"

struct TestSceneImGuiImpl
{
	std::shared_ptr<InputClient> inputClient;
	bool firstFrame;

	TestSceneImGuiImpl() :
		firstFrame(true)
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

void TestSceneImGui::renderUi(RenderTarget& renderTarget)
{
	ImGuiWindowFlags windowFlags = 0;

	ImGui::Begin("scene window", nullptr, windowFlags);
	if (data->firstFrame)
	{
		ImGui::SetWindowSize(ImVec2(200.0f, 100.0f));
		ImGui::SetWindowPos(ImVec2(renderTarget.getWidth() / 2.0f, renderTarget.getHeight() / 2.0f));
	}
	ImGui::End();

	data->firstFrame = false;
}