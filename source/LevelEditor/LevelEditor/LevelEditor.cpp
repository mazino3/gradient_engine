#include "LevelEditor.h"
#include "LevelObject.h"
#include "InputPriorities.h"
#include "Resources.h"
#include "SelectionManager.h"
#include "RaycastManager.h"
#include <Graphics/Renderer.h>
#include <Graphics/OrbitCameraController.h>
#include <Graphics/InputClient.h>
#include <LevelEditor/Util.h>
#include <vector>
#include <Graphics/InputClient.h>
#include <iostream>

struct LevelEditorImpl
{
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<OrbitCameraController> cameraController;
	Resources resources;
	SelectionManager selectionManager;
	RaycastManager raycastManager;


	InputClient inputClient;

	std::vector<std::shared_ptr<LevelObject>> levelObjects;
};

LevelEditor::LevelEditor(RenderTarget& renderTarget)
{
	data = std::make_unique<LevelEditorImpl>();
	data->renderer = std::make_unique<Renderer>(renderTarget);
	auto& camera = data->renderer->getCamera();
	camera.setPerspective(45.0f, (float)renderTarget.getWidth() / (float)renderTarget.getHeight(), 0.1f, 200.0f);
	camera.position = glm::vec3(-5, 0, 5);
	data->cameraController = std::make_unique<OrbitCameraController>(camera, renderTarget.getWidth(), renderTarget.getHeight());
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
	data->renderer->getSettings().fogColor = glm::vec3(0.5f, 0.7f, 0.7f);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			auto levelObject = std::make_shared<LevelObject>(*data->renderer, data->resources, data->selectionManager, data->raycastManager, glm::vec3( + i * 2, + j * 2, 0), glm::vec3(1, 1, 5));
			data->levelObjects.push_back(levelObject);
		}
	}

	GeometryDefinition lineGeometry = Util::createGridGeometry(100, 1, 0.2f);
	auto line = data->renderer->createRenderObject(*data->resources.getWhiteTexture().lock(), lineGeometry, Material()).lock();
	line->transform.scale = glm::vec3(1, 1, 1);
	line->material.diffuse = glm::vec3(0, 0, 0);
	line->material.ambient = glm::vec3(0, 0, 0);
	line->transform.position = glm::vec3(0, 0, 0.055);
	line->castsShadows = false;

	data->inputClient.onMouseMoved([this, &renderTarget](double x, double y) 
		{
			double normalizedX = x / renderTarget.getWidth();
			double normalizedY = y / renderTarget.getHeight();

			normalizedX -= 0.5;
			normalizedY = 0.5 - normalizedY;
			normalizedX *= 2;
			normalizedY *= 2;
			

			Ray ray = data->renderer->getCamera().getMouseRay(normalizedX, normalizedY);
			for (auto& levelObject : data->levelObjects)
			{
				bool intersects = levelObject->getAABB().intersectsWith(ray);
				//levelObject->setOutlineEnabled(intersects);
			}
			return false;
		});

	data->inputClient.onMousePressed([this, &renderTarget](double x, double y, int button)
		{
			double normalizedX = x / renderTarget.getWidth();
			double normalizedY = y / renderTarget.getHeight();

			normalizedX -= 0.5;
			normalizedY = 0.5 - normalizedY;
			normalizedX *= 2;
			normalizedY *= 2;

			std::cout << "x: " << normalizedX << " y: " << normalizedY << std::endl;


			Ray ray = data->renderer->getCamera().getMouseRay(normalizedX, normalizedY);

			data->raycastManager.raycast(ray);

			return false;
		});
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

std::vector<std::pair<float, InputClientBase*>> LevelEditor::getInputClients()
{
	return std::vector<std::pair<float, InputClientBase*>>
	{
		std::make_pair(InputPriorities::EDITOR, & data->cameraController->getInputClient()),
		std::make_pair(InputPriorities::SELECTION, &data->inputClient)
	};
}