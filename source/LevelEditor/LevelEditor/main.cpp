#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include <Graphics/RenderWindow.h>
#include <Graphics/InputClient.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <LevelEditor/LevelParser.h>
#include <LevelEditor/ImGuiBaseWindow.h>
#include <LevelEditor/LevelEditor.h>
#include <fstream>

#include "InputPriorities.h"

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
    window.setClearColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window.getWindowPointer(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);    

    LevelEditor levelEditor(window);

    InputClient imguiInputClient;
    imguiInputClient.onMousePressed([](double xpos, double ypos, int button) 
    {
        return ImGui::GetIO().WantCaptureMouse;
    });
    imguiInputClient.onMouseMoved([](double xpos, double ypos) 
    {
        return ImGui::GetIO().WantCaptureMouse;
    });
    imguiInputClient.onMouseReleased([](double xpos, double ypos, int button) 
    {
        return ImGui::GetIO().WantCaptureMouse;
    });
    window.getInput().addInputClient(imguiInputClient, InputPriorities::IMGUI);

    for (auto& inputClientEntry : levelEditor.getInputClients())
    {
        auto inputClientPtr = inputClientEntry.second;
        auto inputPriority = inputClientEntry.first;
        window.getInput().addInputClient(*inputClientPtr, inputPriority);
    }

    ImGuiBaseWindow guiWindow;
    guiWindow.setSize(100, 200);
    guiWindow.setName("my window");

    while (window.isOpen())
    {
        window.clear();
        window.getInput().processInput();
        levelEditor.render(window, 1.0f / 60.0f);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        guiWindow.render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());        
        window.swapBuffers();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}