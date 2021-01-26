#include "TestSceneFactory.h"
#include "TestSceneImGui.h"
#include "TestSceneRenderer.h"
#include "TestSceneBlur.h"
#include <unordered_map>

enum SceneIds
{
	IMGUI_TEST,
	RENDERER_TEST,
	BLUR_TEST,
	SCENE_COUNT
};

std::vector<TestSceneId> TestSceneFactory::getSceneIds()
{
	static std::vector<TestSceneId> sceneIds;
	for (int i = sceneIds.size(); i < SCENE_COUNT; i++)
	{
		sceneIds.push_back(i);
	}
	return sceneIds;
}

std::string TestSceneFactory::getSceneName(TestSceneId id)
{
	static std::unordered_map<TestSceneId, std::string> sceneNames = 
	{
		{IMGUI_TEST, "ImGui test"},
		{RENDERER_TEST, "Renderer test"},
		{BLUR_TEST, "Blur test"}
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
	case BLUR_TEST:
		return std::make_shared<TestSceneBlur>(renderTarget);
	default:
		return std::shared_ptr<TestSceneBase>();
	}
}

