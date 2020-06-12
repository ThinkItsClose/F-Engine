#pragma once

#include <string>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
private:
	unsigned int width  = 0;
	unsigned int height = 0;

	GLFWwindow* window;

public:
	Window();
	Window(std::string, unsigned int, unsigned int);
	GLFWwindow* GetWindow();

	unsigned int GetWidth();
	unsigned int GetHeight();

};

