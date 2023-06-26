#include "Application.h"

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

#include "Demos/Tests/DemoScene.h"
#include "Demos/Tests/SandboxScene.h"
#include "Demos/Tests/MovingEntity.h"
#include "Demos/Space Raiders/SpaceRaidersScene.h"

#include "glm/glm.hpp"

std::unique_ptr<Window> g_window;

void ScreenshotDemoScene(int argc, char* argv[])
{
    if (argc < 2)
        return;

    std::unique_ptr<Scene> testScene = std::make_unique<Scene>(argv[1]);

    TimeStep timestep(glfwGetTime());

    while (g_window->IsOpen())
    {
        timestep.Update(glfwGetTime());
        testScene->OnUpdate(timestep);
        g_window->SwapBuffers();
    }

    CLOSE_CONSOLE();
}

int main(int argc, char* argv[])
{
    ALLOC_CONSOLE();

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    LOG_INFO("Glfw Intialised");

    /* Imgui Setup */
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    g_window = std::make_unique<Window>(1280, 1080, "Renderer2D", true);
    
    ImGui_ImplOpenGL3_Init("#version 130");

    LOG_INFO("Imgui Intialised");

    if (glewInit() != GLEW_OK)
        return -1;

    LOG_INFO("Glew Intialised");

#ifdef TESTING
    ScreenshotDemoScene(argc, argv);
    return 0;
#endif

    RegisterEntity<Entity>();
    RegisterEntity<MovingEntity>();

    //std::unique_ptr<BasicDemoScene> demoScene = std::make_unique<BasicDemoScene>(8);
    //std::unique_ptr<SandboxScene> sandboxScene = std::make_unique<SandboxScene>(8);
    //std::unique_ptr<Scene> testScene = std::make_unique<Scene>("test.scene");
    std::unique_ptr<SpaceRaidersScene> spaceRaiders = std::make_unique<SpaceRaidersScene>(8);


    //demoScene->Init();
    //sandboxScene->Init();
    spaceRaiders->Init();

    TimeStep timestep(glfwGetTime());

    while (g_window->IsOpen())
    {
        timestep.Update(glfwGetTime());
        spaceRaiders->OnUpdate(timestep);
        g_window->SwapBuffers();
    }

    //demoScene->Save("test.scene");

    CLOSE_CONSOLE();

    return 0;
}