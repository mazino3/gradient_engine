#include "TestSceneBlur.h"
#include "Graphics/BlurShader.h"
#include "Graphics/RenderTexture.h"
#include "Graphics/BypassShader.h"
#include "Graphics/HdrShader.h"
#include <iostream>
#include "imgui.h"

struct TestSceneBlurImpl
{
	RenderTexture renderTexture;
	RenderTexture renderTexture2;
	BlurShader blurShader;
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
	numberOfPasses(1)
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
	
	data->blurShader.bind();
	data->blurShader.setPixelSize(1.0f / (float)renderTarget.getWidth());

	for (int i = 0; i < data->numberOfPasses * 2; i++)
	{
		auto& textureToBind = i % 2 == 0 ? data->renderTexture2 : data->renderTexture;
		auto& textureUniform = i % 2 == 0 ? data->renderTexture : data->renderTexture2;

		textureToBind.bind();
		if (i <= 2)
		{
			textureToBind.setClearColor(glm::vec4(0.1f, 0.0f, 0.2f, 1.0f));
			textureToBind.clear();
		}

		data->blurShader.setHorizontal(i % 2 == 0);
		data->blurShader.setScreenTexture(textureUniform.getRenderedTexture());
		data->screenMesh.draw();
		textureToBind.updateTexture(false);
	}

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