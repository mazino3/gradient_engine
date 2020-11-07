#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>


int main()
{
    if (!glfwInit())
    {
        return -1;
    }

    GLFWwindow* window;
    window = glfwCreateWindow(640, 480, "Hello GLFW", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glClearColor(0.1f, 0.0f, 0.2f, 0.0f);

    while (!glfwWindowShouldClose(window))
    {
        
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(1, 1, 1);
        glBegin(GL_TRIANGLES);
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);
        glVertex3f(1, 1, 0);
        glEnd();
        glFlush();
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
