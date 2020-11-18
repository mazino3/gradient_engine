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

    Transform tm;
    Camera camera;
    camera.position = glm::vec3(-5, 0, 5);
    camera.dirFront = glm::normalize(glm::vec3(1, 0, -1));
    camera.dirUp = glm::normalize(glm::vec3(1, 0, 1));
    camera.setPerspective(45.0f, 640.0f / 480.0f, 0.1f, 200.0f);
    tm.rotation.x = 180.0f;
    //tm.scale *= 3;

    shader3d.setModelMatrix(tm.getWorldMatrix());
    shader3d.setProjectionMatrix(camera.getProjectionMatrix());
    shader3d.setViewMatrix(camera.getViewMatrix());

    Texture diffuseTexture("Assets/Sprites/Brick.png");
    shader3d.setDiffuseTexture(diffuseTexture);

    GeometryDefinition quad(GeometryDefinition::CUBE);
    Mesh mesh(quad);

    while (window.isOpen())
    {
        tm.rotation.x += 30.0f * 1.0f / 60.0f;
        tm.rotation.y += 20.0f * 1.0f / 60.0f;
        //tm.rotation.z += 10.0f * 1.0f / 60.0f;
        shader3d.setModelMatrix(tm.getWorldMatrix());

        window.clear();
        mesh.draw();
        window.swapBuffers();
    }

    glfwTerminate();
    return 0;
}
