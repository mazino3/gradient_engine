#include "TestSceneLine.h"

struct TestSceneLineImpl
{

};

TestSceneLine::TestSceneLine(RenderTarget& renderTarget)
{
	data = std::make_unique<TestSceneLineImpl>();
}

void TestSceneLine::render(RenderTarget& renderTarget, float dt)
{
	//todo: implement
}

void TestSceneLine::renderUi(RenderTarget& renderTarget)
{
	//todo: implement
}