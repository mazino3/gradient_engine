#include "LevelEditor.h"
#include "LevelObject.h"
#include "InputPriorities.h"
#include "Resources.h"
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
	data->renderer->getSettings().fogColor = glm::vec3(0.5f, 0.7f, 0.7f);

	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			//auto levelObject = std::make_shared<LevelObject>(*data->renderer, data->resources, glm::vec3( + i * 10, + j * 10, 0), glm::vec3(1, 1, 5));
			//data->levelObjects.push_back(levelObject);
		}
	}

	GeometryDefinition lineGeometry = Util::createGridGeometry(100, 1, 0.2f);
	auto line = data->renderer->createRenderObject(*data->resources.getWhiteTexture().lock(), lineGeometry, Material()).lock();
	line->transform.scale = glm::vec3(1, 1, 1);
	line->material.diffuse = glm::vec3(0, 0, 0);
	line->material.ambient = glm::vec3(0, 0, 0);
	line->transform.position = glm::vec3(0, 0, 0.055);
	line->castsShadows = false;

	//cylinder:

	auto cylinder = data->renderer->createRenderObject(*data->resources.getWhiteTexture().lock(), GeometryDefinition::createCylinder(100, 1, 4), Material());
	cylinder.lock()->transform.rotation.x = 90.0f;
	cylinder.lock()->transform.position.z = 2.0f;

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
				levelObject->setOutlineEnabled(intersects);
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

			auto lineDef = GeometryDefinition::createLine(ray.origin,
				ray.origin + glm::vec3(ray.direction.x * 100, ray.direction.y * 100, ray.direction.z * 100));
			auto line = data->renderer->createRenderObject(*data->resources.getWhiteTexture().lock(), lineDef, Material()).lock();
			line->material.diffuse = glm::vec3(0, 0, 0);
			line->material.ambient = glm::vec3(0, 0, 0);

			for (auto& levelObject : data->levelObjects)
			{
				bool intersects = levelObject->getAABB().intersectsWith(ray);
				if (intersects)
				{
					auto aabb = levelObject->getAABB();

					std::cout << "intersection!" << std::endl << std::endl;
					std::cout << "aabb params: " << std::endl;
					std::cout << "pos: " << aabb.position.x << " " << aabb.position.y << " " << aabb.position.z << std::endl;
					std::cout << "scale: " << aabb.size.x << " " << aabb.size.y << " " << aabb.size.z << std::endl << std::endl;
					std::cout << "ray params: " << std::endl;
					std::cout << "origin: " << ray.origin.x << " " << ray.origin.y << " " << ray.origin.z << std::endl;
					std::cout << "direction: " << ray.direction.x << " " << ray.direction.y << " " << ray.direction.z << std::endl << std::endl << std::endl;
				}
			}

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