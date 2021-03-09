#include "TestSceneBlurGroup.h"
#include "imgui.h"
#include "Graphics/RenderTexture.h"
#include "Graphics/BypassShader.h"
#include "Graphics/BlurShaderGroup.h"
#include <iostream>

struct TestSceneBlurGroupImpl
{
	RenderTexture renderTexture;
	BypassShader bypassShader;
	BlurShaderGroup blurShaderGroup;

	TestSceneBlurGroupImpl(int width, int height);
};

TestSceneBlurGroupImpl::TestSceneBlurGroupImpl(int width, int height) :
	renderTexture(width, height, RenderTextureType::Integer, false),
	blurShaderGroup(1.0f, 30.0f, 1.0f)
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
	//todo: implement
}

void TestSceneBlurGroup::renderUi(RenderTarget& renderTarget)
{
	//todo: implement
}