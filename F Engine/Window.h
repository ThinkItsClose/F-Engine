#pragma once

#include <string>
#include <GLFW/glfw3.h>
#include <iostream>


class Window
{
private:
	unsigned int width;
	unsigned int height;

	GLFWwindow* window;

public:
	Window(std::string, unsigned int, unsigned int);

};

