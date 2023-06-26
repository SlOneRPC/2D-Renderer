#pragma once

#include <OpenGL/CommonRender.h>

class Window {
public:
	Window(int width, int height, const char* title, bool imguiEnabled = false);
	~Window();

	bool IsOpen();
	void SwapBuffers();
private:
	GLFWwindow* window;
};