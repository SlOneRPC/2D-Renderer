#pragma once

#include <OpenGL/CommonRender.h>

class Window {
public:
	Window(int width, int height, const char* title, bool vSyncEnabled = true, bool imguiEnabled = true);
	~Window();

	bool IsOpen();
	void SwapBuffers();
	GLFWwindow* GetGlFWWindow();
private:
	GLFWwindow* window;
};