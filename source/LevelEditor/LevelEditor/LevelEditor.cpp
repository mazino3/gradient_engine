#include "LevelEditor.h"
#include "Resources.h"
#include <Graphics/Renderer.h>
#include <Graphics/OrbitCameraController.h>
#include <Graphics/InputClient.h>

struct LevelEditorImpl
{
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<OrbitCameraController> cameraController;
	Resources resources;
	InputClient inputClient;
};

LevelEditor::LevelEditor(RenderTarget& renderTarget)
{
	data = std::make_unique<LevelEditorImpl>();
	data->renderer = std::make_unique<Renderer>(renderTarget);
	auto& camera = data->renderer->getCamera();
	camera.setPerspective(45.0f, (float)renderTarget.getWidth() / (float)renderTarget.getHeight(), 0.1f, 200.0f);
	camera.position = glm::vec3(-5, 0, 5);
	data->cameraController = std::make_unique<OrbitCameraController>(camera);
	data->cameraController->setHorizontalAngle(0);
	data->cameraController->setMaxDistance(100);
	data->cameraController->setDistance(10);
	data->cameraController->setVerticalAngle(45.0f);
	
	auto& light = data->renderer->createDirectionalLight();
	light.ambientColor = glm::vec3(0.3f, 0.3f, 0.3f);
	light.diffuseColor = glm::vec3(3.0f, 3.0f, 3.0f);
	light.specularColor = glm::vec3(0.0f, 0.0f, 0.0f);
	light.direction = glm::normalize(glm::vec3(1, 0.3, 1));
	light.shadowsEnabled = true;

	GeometryDefinition quad(GeometryDefinition::CUBE);
	auto floor = data->renderer->createRenderObject(*data->resources.getWhiteTexture().lock(), quad, Material()).lock();
	floor->transform.position = glm::vec3(0, 0, 0);
	floor->transform.scale = glm::vec3(20, 20, 0.1);

	data->renderer->getSettings().bloomEnabled = false;
}

LevelEditor::~LevelEditor()
{

}

void LevelEditor::render(RenderTarget& renderTarget, float dt)
{
	data->cameraController->update(dt);
	renderTarget.bind();
	data->renderer->renderScene();
}