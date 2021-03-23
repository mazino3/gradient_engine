#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "Graphics/RenderWindow.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include "TestSceneFactory.h"

bool getNextSceneWithButtons(TestSceneId& outId)
{
    for (const auto& id : TestSceneFactory::getSceneIds())
    {
        auto sceneName = TestSceneFactory::getSceneName(id);
        if (ImGui::Button(sceneName.c_str()))
        {
            outId = id;
            return true;
        }
    }
    return false;
}

int main()
{
    const char* glsl_version = "#version 130";
    RenderWindow window(800, 600, "Hello GLFW!");
    if (!window.init())
    {
        std::cerr << "failed to create window";
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window.getWindowPointer(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    
    window.setClearColor(glm::vec4(0.1f, 0.0f, 0.2f, 0.0f));

    std::shared_ptr<TestSceneBase> currentScene;

    while (window.isOpen())
    {
        window.clear();

        if (currentScene != nullptr)
        {
            currentScene->render(window, 0.016f);
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

        ImGui::Begin("test window", nullptr, windowFlags);
        ImGui::SetWindowSize(ImVec2(200.0f, 100.0f));
        ImGui::SetWindowPos(ImVec2(0, 0));

        TestSceneId nextSceneId;
        if (getNextSceneWithButtons(nextSceneId))
        {
            if (currentScene != nullptr)
            {
                window.getInput().removeInputClient(currentScene->getInputClient());
            }
            currentScene = TestSceneFactory::createScene(nextSceneId, window);
            if (currentScene != nullptr)
            {
                std::cout << "opening scene with id: " << nextSceneId << std::endl;
                window.getInput().addInputClient(currentScene->getInputClient(), 0.0f);
                currentScene->onDestroy([]() 
                {
                    std::cout << "closing scene" << std::endl;
                });
            }
        }

        ImGui::End();

        if (currentScene != nullptr)
        {
            currentScene->renderUi(window);
        }

        

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window.swapBuffers();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
