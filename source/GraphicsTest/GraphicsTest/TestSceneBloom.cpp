#include <GraphicsTest/TestSceneBloom.h>
#include <Graphics/RenderTexture.h>
#include <Graphics/BloomEffectRenderer.h>
#include <Graphics/Shaders/BypassShader.h>
#include <Graphics/Shaders/HdrShader.h>
#include <Graphics/Colors.h>
#include <imgui.h>
#include <vector>
#include <iostream>

struct TestSceneBloomImpl
{
	RenderTexture renderTexture1;
	RenderTexture renderTexture2;
	RenderTexture renderTexture3;
	BloomEffectRenderer bloomEffectRenderer;
	BypassShader bypassShader;
	HdrShader hdrShader;
	std::vector<std::shared_ptr<Mesh>> quadMeshes;
	Mesh screenMesh;
	int numberOfBlurPasses;

	TestSceneBloomImpl(int width, int height);
};

TestSceneBloomImpl::TestSceneBloomImpl(int width, int height) :
	renderTexture1(width, height, RenderTextureType::Float, false),
	renderTexture2(width, height, RenderTextureType::Float, false),
	renderTexture3(width, height, RenderTextureType::Float, false),
	screenMesh(GeometryDefinition::SCREEN),
	numberOfBlurPasses(5),
	bloomEffectRenderer(renderTexture2, renderTexture3)
{
	if (!renderTexture1.init()) std::cout << "failed to initialize render texture1" << std::endl;
	if (!renderTexture2.init()) std::cout << "failed to initialize render texture2" << std::endl;
	if (!renderTexture3.init()) std::cout << "failed to initialize render texture3" << std::endl;

	for (int i = 0; i < 10; i++)
	{
		std::vector<Vertex> vertices;
		for (auto& vertex : GeometryDefinition::XY_QUAD.vertices)
		{
			vertices.push_back(Vertex(vertex));
			vertices.back().color = glm::vec4(0.1f * i, 0.1f * i, 0.1f * i, 1.0f);
			vertices.back().pos.x = vertices.back().pos.x * 0.1f + (i - 5) * 0.1f;
		}
		GeometryDefinition quadDef(MeshType::Triangles, vertices, GeometryDefinition::XY_QUAD.indices);
		auto quadMesh = std::make_shared<Mesh>(quadDef);
		quadMeshes.push_back(quadMesh);
	}
}

TestSceneBloom::TestSceneBloom(RenderTarget& renderTarget)
{
	data = std::make_shared<TestSceneBloomImpl>(renderTarget.getWidth(), renderTarget.getHeight());
}

void TestSceneBloom::render(RenderTarget& renderTarget, float dt)
{
	data->renderTexture1.bind();
	data->renderTexture1.setClearColor(glm::vec4(0.1f, 0.0f, 0.2f, 1.0f));
	data->renderTexture1.clear();
	data->bypassShader.bind();
	for (auto& quadMesh : data->quadMeshes)
	{
		quadMesh->draw();
	}
	data->renderTexture1.updateTexture(false);

	data->bloomEffectRenderer.setNumberOfBlurPasses(data->numberOfBlurPasses);
	data->bloomEffectRenderer.render(data->renderTexture1);

	renderTarget.bind();
	data->hdrShader.bind();
	data->hdrShader.setContrast(0);
	data->hdrShader.setExposure(1);
	data->hdrShader.setGamma(2.2f);
	data->hdrShader.setGammaCorrectionEnabled(true);
	data->hdrShader.setToneMappingEnabled(true);
	data->hdrShader.setScreenTexture(data->bloomEffectRenderer.getOutputTexture().getRenderedTexture());
	data->screenMesh.draw();
}

void TestSceneBloom::renderUi(RenderTarget& renderTarget)
{
	static bool firstFrame = true;

	ImGui::Begin("Blur settings");
	if (firstFrame)
	{
		firstFrame = false;
		ImGui::SetWindowSize(ImVec2(400.0f, 200.0f));
		ImGui::SetWindowPos(ImVec2(renderTarget.getWidth() / 2.0f, renderTarget.getHeight() - 250.0f));
	}
	ImGui::SliderInt("number of passes", &data->numberOfBlurPasses, 1, 10);
	ImGui::End();
}

