#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "Graphics/RenderWindow.h"
#include "Graphics/BypassShader.h"
#include "Graphics/Shader3d.h"
#include "Graphics/Mesh.h"
#include "Graphics/Transform.h"
#include "Graphics/Camera.h"
#include "Graphics/Texture.h"
#include "Graphics/InputClient.h"
#include "Graphics/OrbitCameraController.h"
#include "Graphics/Renderer.h"

#include <iostream>

int main()
{
    RenderWindow window(640, 480, "Hello GLFW!");
    if (!window.init())
    {
        std::cerr << "failed to create window";
        return -1;
    }
    
    window.setClearColor(glm::vec4(0.1f, 0.0f, 0.2f, 0.0f));

    Renderer renderer;
    auto& camera = renderer.getCamera();
    camera.setPerspective(45.0f, 640.0f / 480.0f, 0.1f, 200.0f);
    OrbitCameraController cameraController(camera);
    window.getInput().addInputClient(cameraController.getInputClient(), 0.0f);

    Material material;
    material.ambient = glm::vec3(1, 1, 1);
    material.diffuse = glm::vec3(1, 1, 1);
    material.specular = glm::vec3(1, 1, 1);
    material.shininess = 50;
    material.alpha = 0.5f;

    GeometryDefinition quad(GeometryDefinition::CUBE);

    Texture diffuseTexture("Assets/Sprites/Brick2_Color.jpg");
    Texture normalTexture("Assets/Sprites/Brick2_Normal.jpg");

    auto& renderObject1 = renderer.createRenderObject(diffuseTexture, normalTexture, quad, material);

    auto& renderObject2 = renderer.createRenderObject(diffuseTexture, normalTexture, quad, material);
    renderObject2.transform.position.x += 2;
    renderObject2.material.alpha = 1.0f;

    auto& renderObject3 = renderer.createRenderObject(diffuseTexture, normalTexture, quad, material);
    renderObject3.transform.position.x -= 2;

    auto& light = renderer.createDirectionalLight();
    light.ambientColor = glm::vec3(0.3f, 0.3f, 0.3f);
    light.diffuseColor = glm::vec3(2.0f, 2.0f, 2.0f);
    light.specularColor = glm::vec3(0.0f, 0.0f, 0.0f);
    light.direction = glm::normalize(glm::vec3(1, 0, 0));
    

    float phase = 0;

    while (window.isOpen())
    {
        phase += 0.01f;
        //tm.rotation.x += 30.0f * 1.0f / 60.0f;
        //tm.rotation.y += 20.0f * 1.0f / 60.0f;
        
        cameraController.update(0.016f);

        window.clear();
        renderer.renderScene();
        window.swapBuffers();
    }

    glfwTerminate();
    return 0;
}
