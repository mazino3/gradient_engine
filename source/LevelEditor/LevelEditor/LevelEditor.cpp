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
	light.diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
	light.specularColor = glm::vec3(0.0f, 0.0f, 0.0f);
	light.direction = glm::normalize(glm::vec3(1, 0.3, 1));
	light.shadowsEnabled = true;

	GeometryDefinition quad(GeometryDefinition::CUBE);
	auto floor = data->renderer->createRenderObject(*data->resources.getWhiteTexture().lock(), quad, Material()).lock();
	floor->transform.position = glm::vec3(0, 0, 0);
	floor->transform.scale = glm::vec3(200, 200, 0.1);

	data->renderer->getSettings().bloomEnabled = false;
	data->renderer->getSettings().fogDistance = 100.0f;
	data->renderer->getSettings().fogColor = glm::vec3(1.0f, 0.5f, 1.0f);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			auto box = data->renderer->createRenderObject(*data->resources.getWhiteTexture().lock(), quad, Material()).lock();
			box->transform.position = glm::vec3(-50 + i * 10, -50 + j * 10, 0);
			box->transform.scale = glm::vec3(1, 1, 5);
			box->material.diffuse = glm::vec3(1.0f, 0.0f, 0.0f);
			box->material.ambient = glm::vec3(0, 0, 0);
		}
	}
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

std::vector<InputClientBase*> LevelEditor::getInputClients()
{
	return std::vector<InputClientBase*>
	{
		&data->cameraController->getInputClient()
	};
}