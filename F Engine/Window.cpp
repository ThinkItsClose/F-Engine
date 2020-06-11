#include "Window.h"


void FrameBufferSizeChangeCallback(GLFWwindow*, int, int);

// Constructor, will be used to generate the GLFW window
Window::Window(std::string windowName, unsigned int mWidth, unsigned int mHeight) {

	glfwInit();

	this->width = mWidth;
	this->height = mHeight;

	// Minimum version of OpenGL 4.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	// Define the window
	this->window = glfwCreateWindow(this->width, this->height, windowName.c_str(), NULL, NULL);

	if (!window)
		std::cout << "Window creation failed\n";

	// Assign the OpenGL context to the window
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeChangeCallback);

}

void FrameBufferSizeChangeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}