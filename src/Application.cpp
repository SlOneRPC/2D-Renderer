#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iomanip>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "OpenGL/Window.h"
#include "OpenGL/Texture.h"
#include "Renderer/Renderer2D.h"

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Imgui Setup */
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    std::unique_ptr<Window> window = std::make_unique<Window>(1280, 1080, "Renderer2D", true);
    
    ImGui_ImplOpenGL3_Init("#version 130");

    if (glewInit() != GLEW_OK)
        return -1;

    std::unique_ptr<Renderer2D> renderer2D = std::make_unique<Renderer2D>();

    std::unique_ptr<Texture> checkerboardTexture = std::make_unique<Texture>(APP_RESOURCE("images/checkerboard.jpg"));

    /* Loop until the user closes the window */
    while (window->IsOpen())
    {
        renderer2D->Begin();
        {
            renderer2D->DrawTexturedQuad({ -0.5f, -0.5f }, { 1.0f, 1.0f }, checkerboardTexture.get());

            //renderer2D->DrawQuad({ -0.5f, -0.5f }, { 1.0f, 1.0f }, { 1.0, 0.f, 0.f, 1.0f });

            renderer2D->DrawTriangle({ -0.2f, -0.4f }, { 0.5f, 0.5f }, { 0.0, 1.f, 0.f, 1.0f });
        }
        renderer2D->End();

        window->SwapBuffers();
    }

    return 0;
}