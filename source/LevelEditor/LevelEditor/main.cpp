#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include <Graphics/RenderWindow.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <LevelEditor/LevelParser.h>
#include <LevelEditor/ImGuiBaseWindow.h>
#include <fstream>

int main()
{
    LevelData levelData;
    levelData.objects.push_back(LevelDataObject(glm::vec3(1, 2, 3), glm::vec3(4, 5, 6)));
    LevelParser::saveToFile(levelData, "testLevel.json");

    const char* glsl_version = "#version 130";
    RenderWindow window(800, 600, "Hello GLFW!");
    if (!window.init())
    {
        std::cerr << "failed to create window";
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO&    io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window.getWindowPointer(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    window.setClearColor(glm::vec4(0.1f, 0.0f, 0.2f, 0.0f));

    ImGuiBaseWindow guiWindow;
    guiWindow.setName("test window");
    guiWindow.setSize(400, 200);
    guiWindow.setPos(100, 100);

    guiWindow.createButton(50, 50, "button1");
    guiWindow.createButton(150, 50, "button2");
    guiWindow.createButton(50, 150, "button3");
    guiWindow.createButton(150, 150, "button4");

    while (window.isOpen())
    {
        window.clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        guiWindow.render();

        /*
        if (ImGui::Button("test button"))
        {
            std::cout << "test button pressed" << std::endl;
        }
        
        ImGui::SetCursorPosX(10.0f);

        if (ImGui::Button("test button 2"))
        {
            std::cout << "test button pressed" << std::endl;
        }
        */
     
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());        

        auto io = ImGui::GetIO();
        if (io.WantCaptureMouse)
        {
            std::cout << "capturing mouse event" << std::endl;
        }

        window.swapBuffers();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}