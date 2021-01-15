#include "TestSceneFactory.h"
#include "TestSceneImGui.h"
#include <unordered_map>

enum SceneIds
{
	IMGUI_TEST = 0
};

std::vector<TestSceneId> TestSceneFactory::getSceneIds()
{
	static std::vector<TestSceneId> sceneIds = 
	{
		IMGUI_TEST
	};
	return sceneIds;
}

std::string TestSceneFactory::getSceneName(TestSceneId id)
{
	static std::unordered_map<TestSceneId, std::string> sceneNames = 
	{
		{IMGUI_TEST, "ImGui test"},
	};

	if (sceneNames.find(id) != sceneNames.end())
	{
		return sceneNames[id];
	}
	
	return "noname test scene";
}

std::shared_ptr<TestSceneBase> TestSceneFactory::createScene(TestSceneId id)
{
	switch (id)
	{
	case IMGUI_TEST:
		return std::make_shared<TestSceneImGui>();
	default:
		return std::shared_ptr<TestSceneBase>();
	}
}

