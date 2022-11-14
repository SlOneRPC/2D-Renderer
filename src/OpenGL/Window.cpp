#include "Window.h"
#include "imgui_impl_glfw.h"

Window::Window(int width, int height, const char* title, bool imguiEnabled)
{
	window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
        glfwTerminate();

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

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
