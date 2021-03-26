#include <GraphicsTest/TestSceneBase.h>
#include <Graphics/InputClient.h>
#include <vector>

struct TestSceneBaseImpl
{
	std::function<void(void)> onDestroyCallback;

	std::vector<InputClientBase*> inputClients;

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

std::vector<InputClientBase*> TestSceneBase::getInputClients()
{
	return data->inputClients;
}

void TestSceneBase::onDestroy(std::function<void(void)> onDestroyCallback)
{
	data->onDestroyCallback = onDestroyCallback;
}