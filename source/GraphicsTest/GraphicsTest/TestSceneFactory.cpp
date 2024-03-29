#include <GraphicsTest/TestSceneFactory.h>
#include <GraphicsTest/TestSceneImGui.h>
#include <GraphicsTest/TestSceneRenderer.h>
#include <GraphicsTest/TestSceneBlur.h>
#include <GraphicsTest/TestSceneBlurGroup.h>
#include <GraphicsTest/TestSceneBloom.h>
#include <GraphicsTest/TestSceneLine.h>
#include <unordered_map>

enum SceneIds
{
	IMGUI_TEST,
	RENDERER_TEST,
	BLUR_TEST,
	BLUR_GROUP_TEST,
	BLOOM_TEST,
	LINE_TEST,
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
		{BLUR_TEST, "Blur test"},
		{BLUR_GROUP_TEST, "Blur group test"},
		{BLOOM_TEST, "Bloom test"},
		{LINE_TEST, "Line test"}
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
	case BLUR_GROUP_TEST:
		return std::make_shared<TestSceneBlurGroup>(renderTarget);
	case BLOOM_TEST:
		return std::make_shared<TestSceneBloom>(renderTarget);
	case LINE_TEST:
		return std::make_shared<TestSceneLine>(renderTarget);
	default:
		return std::shared_ptr<TestSceneBase>();
	}
}

