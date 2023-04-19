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
#include "Demos/Tests/SpinningEntity.h"
#include "Demos/Tests/BasicQuadEntity.h"
#include "Demos/Space Raiders/SpaceRaidersScene.h"
#include "Demos/Space Raiders/Entities/Alien.h"
#include "Demos/Space Raiders/Entities/Rocket.h"
#include "Demos/Space Raiders/Entities/Wall.h"
#include "Demos/Space Raiders/Entities/EndGame.h"

#include "glm/glm.hpp"

std::unique_ptr<Window> g_window;

// If performing a lib build, then we need to strip the main method
#ifndef BUILD_LIB

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

    g_window = std::make_unique<Window>(1280, 1080, "Renderer2D");
    
    ImGui_ImplOpenGL3_Init("#version 130");

    LOG_INFO("Imgui Intialised");

    if (glewInit() != GLEW_OK)
        return -1;

    LOG_INFO("Glew Intialised");

    RegisterEntity<Entity>();
    RegisterEntity<MovingEntity>();
    RegisterEntity<Rocket>();
    RegisterEntity<Wall>();
    RegisterEntity<Alien>();
    RegisterEntity<EndGame>();
    RegisterEntity<SpinningEntity>();
    RegisterEntity<BasicQuadEntity>();

    Scene* scene;

    // If a scene has been passed in as an arguement then load that
    if (argc >= 2) 
    {
        scene = new Scene(argv[1]);
    }
    else 
    {
        // load space raiders scene by default
        scene = new SpaceRaidersScene(8);
        scene->Init();
    }

    TimeStep timestep(glfwGetTime());

    while (g_window->IsOpen())
    {
        timestep.Update(glfwGetTime());
        scene->BeginScene(timestep);
        g_window->SwapBuffers();
    }

    delete scene;

    CLOSE_CONSOLE();

    return 0;
}

#endif // !BUILD_LIB