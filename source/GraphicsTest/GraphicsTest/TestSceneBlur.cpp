#include <GraphicsTest/TestSceneBlur.h>
#include <Graphics/Shaders/BlurShader.h>
#include <Graphics/RenderTexture.h>
#include <Graphics/Shaders/BypassShader.h>
#include <Graphics/Shaders/HdrShader.h>
#include <Graphics/BlurEffectRenderer.h>
#include <iostream>
#include <imgui.h>

struct TestSceneBlurImpl
{
	RenderTexture renderTexture;
	RenderTexture renderTexture2;
	BlurEffectRenderer blurEffectRenderer;
	BypassShader bypassShader;
	HdrShader hdrShader;

	Mesh quadMesh;
	Mesh screenMesh;

	int numberOfPasses;

	TestSceneBlurImpl(int width, int height);
};

TestSceneBlurImpl::TestSceneBlurImpl(int width, int height) :
	renderTexture(width, height, RenderTextureType::Integer, false),
	renderTexture2(width, height, RenderTextureType::Integer, false),
	quadMesh(GeometryDefinition::XY_QUAD),
	screenMesh(GeometryDefinition::SCREEN),
	numberOfPasses(1),
	blurEffectRenderer(renderTexture2)
{
	if (!renderTexture.init())
	{
		std::cout << "failed to initialize render texture" << std::endl;
	}
	if (!renderTexture2.init())
	{
		std::cout << "failed to initialize render texture 2" << std::endl;
	}
}

TestSceneBlur::TestSceneBlur(RenderTarget& renderTarget)
{
	data = std::make_shared<TestSceneBlurImpl>(renderTarget.getWidth(), renderTarget.getHeight());
}

void TestSceneBlur::render(RenderTarget& renderTarget, float dt)
{
	data->renderTexture.bind();
	data->renderTexture.setClearColor(glm::vec4(0.1f, 0.0f, 0.2f, 1.0f));
	data->renderTexture.clear();
	data->bypassShader.bind();
	data->quadMesh.draw();
	data->renderTexture.updateTexture(false);
	
	data->blurEffectRenderer.setNumberOfPasses(data->numberOfPasses);
	data->blurEffectRenderer.render(data->renderTexture);

	renderTarget.bind();
	data->hdrShader.bind();
	data->hdrShader.setContrast(0);
	data->hdrShader.setExposure(1);
	data->hdrShader.setGamma(1);
	data->hdrShader.setGammaCorrectionEnabled(false);
	data->hdrShader.setToneMappingEnabled(false);
	data->hdrShader.setScreenTexture(data->renderTexture.getRenderedTexture());
	data->screenMesh.draw();
}

void TestSceneBlur::renderUi(RenderTarget& renderTarget)
{
	static bool firstFrame = true;

	ImGui::Begin("Blur settings");
	if (firstFrame)
	{
		firstFrame = false;
		ImGui::SetWindowSize(ImVec2(400.0f, 200.0f));
		ImGui::SetWindowPos(ImVec2(renderTarget.getWidth() / 2.0f, renderTarget.getHeight() - 250.0f));
	}	
	ImGui::SliderInt("number of passes", &data->numberOfPasses, 1, 10);
	ImGui::End();
}