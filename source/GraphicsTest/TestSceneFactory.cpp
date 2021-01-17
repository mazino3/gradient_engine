#include "TestSceneFactory.h"
#include "TestSceneImGui.h"
#include "TestSceneRenderer.h"
#include <unordered_map>

enum SceneIds
{
	IMGUI_TEST = 0,
	RENDERER_TEST = 1
};

std::vector<TestSceneId> TestSceneFactory::getSceneIds()
{
	static std::vector<TestSceneId> sceneIds = 
	{
		IMGUI_TEST,
		RENDERER_TEST
	};
	return sceneIds;
}

std::string TestSceneFactory::getSceneName(TestSceneId id)
{
	static std::unordered_map<TestSceneId, std::string> sceneNames = 
	{
		{IMGUI_TEST, "ImGui test"},
		{RENDERER_TEST, "Renderer test"}
	};

	if (sceneNames.find(id) != sceneNames.end())
	{
		return sceneNames[id];
	}
	
	return "noname test scene";
}

std::shared_ptr<TestSceneBase> TestSceneFactory::createScene(TestSceneId id, RenderTarget& renderTarget)
{
	switch (id)
	{
	case IMGUI_TEST:
		return std::make_shared<TestSceneImGui>();
	case RENDERER_TEST:
		return std::make_shared<TestSceneRenderer>(renderTarget);
	default:
		return std::shared_ptr<TestSceneBase>();
	}
}

