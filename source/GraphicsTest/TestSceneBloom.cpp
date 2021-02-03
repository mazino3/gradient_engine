#include "TestSceneBloom.h"
#include "Graphics/RenderTexture.h"
#include "Graphics/BloomEffectRenderer.h"
#include "Graphics/BypassShader.h"
#include "Graphics/HdrShader.h"
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
	renderTexture1(width, height, RenderTextureType::Integer, false),
	renderTexture2(width, height, RenderTextureType::Integer, false),
	renderTexture3(width, height, RenderTextureType::Integer, false),
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
			vertices.push_back(Vertex(vertex.pos));
			vertices.back().pos.x = vertices.back().pos.x * 0.1f + (i - 5) * 0.1f;
		}
		GeometryDefinition quadDef(MeshType::Triangles, vertices, GeometryDefinition::XY_QUAD.indices);
		auto quadMesh = std::make_shared<Mesh>(quadDef);
		quadMeshes.push_back(quadMesh);
	}
}

TestSceneBloom::TestSceneBloom(RenderTarget& renderTarget)
{
	data = std::make_shared<TestSceneBloomImpl>();
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
	data->hdrShader.setGamma(1);
	data->hdrShader.setGammaCorrectionEnabled(false);
	data->hdrShader.setToneMappingEnabled(false);
	data->hdrShader.setScreenTexture(data->bloomEffectRenderer.getOutputTexture().getRenderedTexture());
	data->screenMesh.draw();
}

void TestSceneBloom::renderUi(RenderTarget& renderTarget)
{
	//todo: implement
}

