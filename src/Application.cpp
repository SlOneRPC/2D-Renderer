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

    //std::unique_ptr<Renderer2D> renderer2D = std::make_unique<Renderer2D>();

    //std::unique_ptr<Texture> checkerboardTexture = std::make_unique<Texture>(APP_RESOURCE("images/checkerboard.jpg"));


    //float camZoom = 4.0f;
    //OrthographicCamera camera(-camZoom, camZoom, -camZoom, camZoom);
    //camera.SetPosition({ 0.5f, 0.5f, 0.0f });

    //glm::vec2 quadTransform(-0.5f, -0.5f);
    //glm::vec2 quadScale(2.f, 2.f);

    ///* Loop until the user closes the window */
    //while (window->IsOpen())
    //{
    //    renderer2D->Begin(camera);
    //    {
    //        renderer2D->DrawTexturedQuad(quadTransform, quadScale, checkerboardTexture.get());

    //        renderer2D->DrawQuad({ -0.5f, -0.5f }, { 1.0f, 1.0f }, { 1.0, 0.f, 0.f, 1.0f });

    //        //renderer2D->DrawTriangle({ -0.2f, -0.4f }, { 2.5f, 2.5f }, { 0.0, 1.f, 0.f, 1.0f });
    //        
    //        {
    //            ImGui::Text("Textured Quad Transform");
    //            ImGui::DragFloat("Quad x", &quadTransform.x);
    //            ImGui::DragFloat("Quad y", &quadTransform.y);

    //            ImGui::DragFloat("Scale x", &quadScale.x);
    //            ImGui::DragFloat("Scale y", &quadScale.y);

    //            ImGui::Text("Camera Position");
    //            glm::vec3 camPosition(camera.GetPosition());
    //            if (ImGui::DragFloat("Cam x", &camPosition.x) ||
    //                ImGui::DragFloat("Cam y", &camPosition.y)) {
    //                camera.SetPosition(camPosition);
    //            }

    //            ImGui::Text("Camera Zoom");
    //            if (ImGui::DragFloat("Cam Zoom", &camZoom)) {
    //                camera.SetProjection(-camZoom, camZoom, -camZoom, camZoom);
    //            }
    //        }
    //    }
    //    renderer2D->End();

    //    window->SwapBuffers();
    //}

    //std::unique_ptr<BasicDemoScene> demoScene = std::make_unique<BasicDemoScene>(8);
    std::unique_ptr<SandboxScene> sandboxScene = std::make_unique<SandboxScene>(8);


    //demoScene->Init();
    sandboxScene->Init();

    float lastFrameTime = glfwGetTime();
    TimeStep timestep;

    while (window->IsOpen())
    {
        float time = glfwGetTime();
        timestep = time - lastFrameTime;
        lastFrameTime = time;


        sandboxScene->OnUpdate(timestep);
        window->SwapBuffers();
    }

    CLOSE_CONSOLE();

    return 0;
}