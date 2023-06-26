#include "Window.h"
#include "imgui_impl_glfw.h"

#ifdef TESTING
#include "Scene/Scene.h"
#include "Core/Logging.h"
#endif

Window::Window(int width, int height, const char* title, bool vSyncEnabled, bool imguiEnabled)
{
	window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
        glfwTerminate();

    glfwMakeContextCurrent(window);
    glfwSwapInterval(vSyncEnabled ? 1 : 0); // Enable vsync

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) 
    {
            if (width > 0 && height > 0) 
            {
                glViewport(0, 0, width, height);
            }
    });

#ifdef TESTING
    glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused)
    {
            if (focused)
            {
                updateFrame = true;
            }
    });
#endif

    if (imguiEnabled)
        ImGui_ImplGlfw_InitForOpenGL(window, true);
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::IsOpen()
{
    return !glfwWindowShouldClose(window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(window);
}

GLFWwindow* Window::GetGlFWWindow()
{
    return window;
}