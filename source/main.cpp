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

    Shader3d shader3d;
    shader3d.bind();

    Camera camera;
    camera.setPerspective(45.0f, 640.0f / 480.0f, 0.1f, 200.0f);
    OrbitCameraController cameraController(camera);
    window.getInput().addInputClient(cameraController.getInputClient(), 0.0f);

    //camera.setOrtho(-6.4, 6.4, -4.8, 4.8, 0.1f, 200.0f);

    shader3d.setProjectionMatrix(camera.getProjectionMatrix());
    shader3d.setViewMatrix(camera.getViewMatrix());

    Texture diffuseTexture("Assets/Sprites/Brick2_Color.jpg");
    Texture normalTexture("Assets/Sprites/Brick2_Normal.jpg");
    shader3d.setDiffuseTexture(diffuseTexture);
    shader3d.setNormalTexture(normalTexture);
    shader3d.setNormalMapEnabled(true);

    //setting up lights

    Material material;
    material.ambient = glm::vec3(1, 1, 1);
    material.diffuse = glm::vec3(1, 1, 1);
    material.specular = glm::vec3(1, 1, 1);
    material.shininess = 50;

    
    DirectionalLight light;
    light.ambientColor = glm::vec3(0.3f, 0.3f, 0.3f);
    light.diffuseColor = glm::vec3(2.0f, 2.0f, 2.0f);
    light.specularColor = glm::vec3(0.0f, 0.0f, 0.0f);
    light.direction = glm::normalize(glm::vec3(1, 0, 0));
    

    /*
    PositionalLight light;
    light.ambientColor = glm::vec3(0.2f, 0.2f, 0.2f);
    light.diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
    light.specularColor = glm::vec3(1.0f, 1.0f, 1.0f);
    light.diffuseColor *= 200;
    light.specularColor *= 200;
    light.position = glm::vec3(0, 0, 0.5);
    light.constantAttenuation = 1;
    light.linearAttenuation = 2;
    light.quadraticAttenuation = 1;
    */

    shader3d.setCurrentMaterialIndex(0);
    shader3d.setMaterial(material, 0);
    //shader3d.setPositionalLightsCount(1);
    //shader3d.setPositionalLight(light, 0);
    shader3d.setDirectionalLightsCount(1);
    shader3d.setDirectionalLight(light, 0);
    shader3d.setEyeDirection(camera.dirFront);
    
    
    Transform tm;
    tm.position = glm::vec3(0.0f, 0.0f, 0.0f);
    tm.scale.x = 3;
    tm.scale.y = 3;
    tm.scale.z = 3;
    GeometryDefinition quad(GeometryDefinition::CUBE);
    GeometryDefinition torus(GeometryDefinition::createTorus(100, 1, 0.4));
    //GeometryDefinition sphere(GeometryDefinition::createSphere(100));
    Mesh mesh(quad);

    float phase = 0;

    while (window.isOpen())
    {
        phase += 0.01f;
        //tm.rotation.x += 30.0f * 1.0f / 60.0f;
        //tm.rotation.y += 20.0f * 1.0f / 60.0f;
        
        cameraController.update(0.016f);
        shader3d.setProjectionMatrix(camera.getProjectionMatrix());
        shader3d.setViewMatrix(camera.getViewMatrix());
        shader3d.setModelMatrix(tm.getWorldMatrix());
        shader3d.setEyeDirection(camera.dirFront);
        glm::mat4x4 modelViewMatrix = camera.getViewMatrix() * tm.getWorldMatrix();
        shader3d.setNormalMatrix(glm::transpose(glm::inverse(modelViewMatrix)));


        //tm.scale.x = 5 + sinf(phase) * 2;
        //tm.scale.z = 5 + cosf(phase * 3.1415) * 2;
        shader3d.setTextureScalingEnabled(true);
        shader3d.setTextureScale(tm.scale);

        window.clear();
        mesh.draw();
        window.swapBuffers();
    }

    glfwTerminate();
    return 0;
}
