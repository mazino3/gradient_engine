#include "TestSceneBlurGroup.h"
#include "imgui.h"
#include "Graphics/RenderTexture.h"
#include "Graphics/Shaders/BypassShader.h"
#include "Graphics/BlurShaderGroup.h"
#include <iostream>

struct TestSceneBlurGroupImpl
{
	RenderTexture renderTexture;
	BypassShader bypassShader;
	BlurShaderGroup blurShaderGroup;
	Mesh quadMesh;
	Mesh screenMesh;
	float radius;

	TestSceneBlurGroupImpl(int width, int height);
};

TestSceneBlurGroupImpl::TestSceneBlurGroupImpl(int width, int height) :
	renderTexture(width, height, RenderTextureType::Integer, false),
	blurShaderGroup(1.0f, 30.0f, 1.0f),
	quadMesh(GeometryDefinition::XY_QUAD),
	screenMesh(GeometryDefinition::SCREEN),
	radius(10.0f)
{
	if (!renderTexture.init())
	{
		std::cout << "failed to initialize render texture in TestSceneBlurGroup" << std::endl;
	}
}

TestSceneBlurGroup::TestSceneBlurGroup(RenderTarget& renderTarget)
{
	data = std::make_shared<TestSceneBlurGroupImpl>(renderTarget.getWidth(), renderTarget.getHeight());
}

void TestSceneBlurGroup::render(RenderTarget& renderTarget, float dt)
{
	data->renderTexture.bind();
	data->renderTexture.setClearColor(glm::vec4(0.1f, 0.0f, 0.2f, 1.0f));
	data->renderTexture.clear();
	data->bypassShader.bind();
	data->quadMesh.draw();
	data->renderTexture.updateTexture(false);

	renderTarget.bind();
	data->blurShaderGroup.setRadius(data->radius);
	data->blurShaderGroup.bind(data->renderTexture.getRenderedTexture(), 1.0f / (float)data->renderTexture.getWidth(), true);
	data->screenMesh.draw();
}

void TestSceneBlurGroup::renderUi(RenderTarget& renderTarget)
{
	static bool firstFrame = true;

	ImGui::Begin("Blur radius");
	if (firstFrame)
	{
		firstFrame = false;
		ImGui::SetWindowSize(ImVec2(400.0f, 200.0f));
		ImGui::SetWindowPos(ImVec2(renderTarget.getWidth() / 2.0f, renderTarget.getHeight() - 250.0f));
	}
	ImGui::SliderFloat("radius", &data->radius, 1.0f, 30.0f);
	ImGui::End();
}