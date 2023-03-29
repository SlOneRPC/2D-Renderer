#include "Input.h"
#include "Application.h"

#include <GLFW/glfw3.h>

bool InputHandler::IsKeyPressed(int keycode)
{
	auto state = glfwGetKey(g_window->GetGlFWWindow(), keycode);
	return state == GLFW_PRESS;
}

bool InputHandler::IsMouseButtonPressed(int button)
{
	auto state = glfwGetMouseButton(g_window->GetGlFWWindow(), button);
	return state == GLFW_PRESS;
}