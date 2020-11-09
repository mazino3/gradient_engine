#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "Graphics/RenderWindow.h"
#include "Graphics/BypassShader.h"
#include "Graphics/Mesh.h"

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

    BypassShader bypassShader;
    bypassShader.bind();

    GeometryDefinition quad(GeometryDefinition::XY_QUAD);
    Mesh mesh(quad);

    while (window.isOpen())
    {
        window.clear();
        mesh.draw();
        window.swapBuffers();
    }

    glfwTerminate();
    return 0;
}
