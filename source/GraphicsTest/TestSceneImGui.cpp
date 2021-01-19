#include "TestSceneImGui.h"
#include "Graphics/InputClient.h"
#include "imgui.h"

struct TestSceneImGuiImpl
{
	InputClient inputClient;
	bool firstFrame;

	TestSceneImGuiImpl() :
		firstFrame(true)
	{}
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