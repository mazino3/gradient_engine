#include "TestSceneBase.h"

struct TestSceneBaseImpl
{
	std::function<void(void)> onDestroyCallback;

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

void TestSceneBase::onDestroy(std::function<void(void)> onDestroyCallback)
{
	data->onDestroyCallback = onDestroyCallback;
}