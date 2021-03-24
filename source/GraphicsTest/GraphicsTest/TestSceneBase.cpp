#include <GraphicsTest/TestSceneBase.h>
#include <Graphics/InputClient.h>

struct TestSceneBaseImpl
{
	std::function<void(void)> onDestroyCallback;

	InputClient inputClient;

	TestSceneBaseImpl() : 
		onDestroyCallback([](){})
	{}
};

TestSceneBase::TestSceneBase()
{
	data = std::make_shared<TestSceneBaseImpl>();
}

TestSceneBase::~TestSceneBase()
{
	data->onDestroyCallback();
}

InputClientBase& TestSceneBase::getInputClient()
{
	return data->inputClient;
}

void TestSceneBase::onDestroy(std::function<void(void)> onDestroyCallback)
{
	data->onDestroyCallback = onDestroyCallback;
}