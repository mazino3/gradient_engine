#include "TestSceneBlur.h"
#include "Graphics/BlurShader.h"

struct TestSceneBlurImpl
{

};

TestSceneBlur::TestSceneBlur()
{
	data = std::make_shared<TestSceneBlurImpl>();
}

void TestSceneBlur::render(RenderTarget& renderTarget, float dt)
{
	//todo: implement
}

void TestSceneBlur::renderUi(RenderTarget& renderTarget)
{
	//todo: implement
}