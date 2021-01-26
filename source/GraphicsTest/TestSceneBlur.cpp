#include "TestSceneBlur.h"
#include "Graphics/BlurShader.h"
#include "Graphics/RenderTexture.h"
#include "Graphics/BypassShader.h"
#include "Graphics/HdrShader.h"
#include <iostream>

struct TestSceneBlurImpl
{
	RenderTexture renderTexture;
	RenderTexture renderTexture2;
	BlurShader blurShader;
	BypassShader bypassShader;
	HdrShader hdrShader;

	Mesh quadMesh;
	Mesh screenMesh;

	TestSceneBlurImpl(int width, int height);
};

TestSceneBlurImpl::TestSceneBlurImpl(int width, int height) :
	renderTexture(width, height, RenderTextureType::Integer, false),
	renderTexture2(width, height, RenderTextureType::Integer, false),
	quadMesh(GeometryDefinition::XY_QUAD),
	screenMesh(GeometryDefinition::SCREEN)
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
	
	data->renderTexture2.bind();
	data->renderTexture2.setClearColor(glm::vec4(0.1f, 0.0f, 0.2f, 1.0f));
	data->renderTexture2.clear();
	data->blurShader.bind();
	data->blurShader.setPixelSize(1.0f / (float)renderTarget.getWidth());
	data->blurShader.setHorizontal(true);
	data->blurShader.setScreenTexture(data->renderTexture.getRenderedTexture());
	data->screenMesh.draw();
	data->renderTexture2.updateTexture(false);

	renderTarget.bind();
	data->hdrShader.bind();
	data->hdrShader.setContrast(0);
	data->hdrShader.setExposure(1);
	data->hdrShader.setGamma(1);
	data->hdrShader.setGammaCorrectionEnabled(false);
	data->hdrShader.setToneMappingEnabled(false);
	data->hdrShader.setScreenTexture(data->renderTexture2.getRenderedTexture());
	data->screenMesh.draw();
}

void TestSceneBlur::renderUi(RenderTarget& renderTarget)
{
	//todo: implement
}