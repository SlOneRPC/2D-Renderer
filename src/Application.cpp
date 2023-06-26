#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iomanip>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "OpenGL/Window.h"
#include "OpenGL/Texture.h"
#include "OpenGL/OrthographicCamera.h"
#include "Renderer/Renderer2D.h"
#include "Core/Logging.h"
#include "Core/TimeStep.h"

#include "Demos/DemoScene.h"
#include "Demos/SandboxScene.h"

#include "glm/glm.hpp"

int main(void)
{
    ALLOC_CONSOLE();

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    LOG_INFO("Glfw Intialised");

    /* Imgui Setup */
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    std::unique_ptr<Window> window = std::make_unique<Window>(1280, 1080, "Renderer2D", true);
    
    ImGui_ImplOpenGL3_Init("#version 130");

    LOG_INFO("Imgui Intialised");

    if (glewInit() != GLEW_OK)
        return -1;

    LOG_INFO("Glew Intialised");

    //std::unique_ptr<BasicDemoScene> demoScene = std::make_unique<BasicDemoScene>(8);
    std::unique_ptr<SandboxScene> sandboxScene = std::make_unique<SandboxScene>(8);

    //demoScene->Init();
    sandboxScene->Init();

    TimeStep timestep(glfwGetTime());

    while (window->IsOpen())
    {
        timestep.Update(glfwGetTime());
        sandboxScene->OnUpdate(timestep);
        window->SwapBuffers();
    }

    sandboxScene->Save("test.scene");

    CLOSE_CONSOLE();

    return 0;
}