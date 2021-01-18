#include "TestSceneRenderer.h"
#include "Graphics/InputClient.h"
#include "Graphics/Renderer.h"
#include "Graphics/FreeCameraController.h"

struct TestSceneRendererImpl
{
	std::shared_ptr<InputClient> inputClient;
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<FreeCameraController> cameraController;
    std::unique_ptr<Texture> diffuseTexture;
    std::unique_ptr<Texture> normalTexture;

	TestSceneRendererImpl();
};

TestSceneRendererImpl::TestSceneRendererImpl()
{
	inputClient = std::make_shared<InputClient>();
}

TestSceneRenderer::TestSceneRenderer(RenderTarget& renderTarget)
{
	data = std::make_shared<TestSceneRendererImpl>();
	data->renderer = std::make_unique<Renderer>(renderTarget);
	auto& camera = data->renderer->getCamera();
	data->cameraController = std::make_unique<FreeCameraController>(camera);
	data->cameraController->setOnlyRotationMode(false);
	data->cameraController->setCameraDirection(glm::normalize(glm::vec3(1, 0, -1)));

    Material material;
    material.ambient = glm::vec3(1, 1, 1);
    material.diffuse = glm::vec3(1, 1, 1);
    material.specular = glm::vec3(1, 1, 1);
    material.shininess = 50;
    material.alpha = 1.0f;

    GeometryDefinition quad(GeometryDefinition::CUBE);

    data->diffuseTexture = std::make_unique<Texture>("Assets/Sprites/Scifi_Color.png");
    data->normalTexture = std::make_unique<Texture>("Assets/Sprites/Scifi_Normal.png");

    auto& renderObject1 = data->renderer->createRenderObject(*data->diffuseTexture, *data->normalTexture, quad, material);
    renderObject1.material.alpha = 1.0f;
    renderObject1.textureScalingEnabled = true;
    //renderObject1.textureScaleMultiplier = 0.25f;

    auto& renderObject2 = data->renderer->createRenderObject(*data->diffuseTexture, *data->normalTexture, quad, material);
    renderObject2.transform.scale.z = 0.1;
    renderObject2.transform.scale.x = 20;
    renderObject2.transform.scale.y = 20;
    renderObject2.transform.position.z -= 0.4;
    renderObject2.textureScalingEnabled = true;
    renderObject2.material.alpha = 1.0f;
    renderObject2.material.ambient = glm::vec3(0.2, 1.0, 0.2);
    renderObject2.material.diffuse = glm::vec3(0.2, 1.0, 0.2);

    auto& renderObject3 = data->renderer->createRenderObject(*data->diffuseTexture, *data->normalTexture, quad, material);
    renderObject3.transform.position.x -= 2;

    auto& torus = data->renderer->createRenderObject(*data->diffuseTexture, GeometryDefinition::createTorus(100, 1, 0.3f), material);
    torus.transform.position.y += 4;
    torus.transform.rotation.x = 90.0f;
    torus.material.alpha = 1.0f;
    torus.material.ambient = glm::vec3(1.0, 0.2, 0.2);
    torus.material.diffuse = glm::vec3(1.0, 0.2, 0.2);

    auto& light = data->renderer->createDirectionalLight();
    light.ambientColor = glm::vec3(0.3f, 0.3f, 0.3f);
    light.diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
    light.specularColor = glm::vec3(0.0f, 0.0f, 0.0f);
    light.direction = glm::normalize(glm::vec3(1, 0.3, 1));
    light.shadowsEnabled = true;
}

std::shared_ptr<InputClientBase> TestSceneRenderer::getInputClient()
{
	return data->inputClient;
}

void TestSceneRenderer::render(RenderTarget& renderTarget, float dt)
{
    data->cameraController->update(dt);
    data->renderer->renderScene();
}

void TestSceneRenderer::renderUi(RenderTarget& renderTarget)
{
	//todo: implement
}