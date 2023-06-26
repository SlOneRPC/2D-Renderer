#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iomanip>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Demos/QuadDemo.h"
#include "Demos/ChessBoardDemo.h"
#include "Demos/TextureDemo.h"
#include <vector>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 1080, "OpenGL Demo", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    if (glewInit() != GLEW_OK)
        return -1;

    /* Imgui Setup */
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    bool show_demo_window = true;

  
    std::vector<Demo*> demos;

    demos.push_back((Demo*)new QuadDemo);
    demos.push_back((Demo*)new TextureDemo);
    demos.push_back((Demo*)new ChessBoardDemo);

    Demo* currentDemo = demos[0];

    currentDemo->Init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        for (Demo* demo : demos) 
        {
            if (ImGui::Button(demo->GetDemoName().c_str())) 
            {
                currentDemo->Shutdown();
                currentDemo = demo;
                currentDemo->Init();
            }
        }

        ImGui::Separator();

        currentDemo->OnRender();

        currentDemo->OnImguiRender();

       // ImGui::ShowDemoWindow(&show_demo_window);
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}