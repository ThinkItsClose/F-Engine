#include "Window.h"

void FrameBufferSizeChangeCallback(GLFWwindow*, int, int);

// Constructor, will be used to generate the GLFW window
Window::Window(std::string windowName, unsigned int mWidth, unsigned int mHeight) {

	width = mWidth;
	height = mHeight;

	// Define the window
	window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

	if (!window)
		std::cout << "Window creation failed\n";

	// Assign the OpenGL context to the window
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeChangeCallback);

	// Turn on v sync
	glfwSwapInterval(1);

}

// Empty constructor so pointers can be used
Window::Window(){}

GLFWwindow* Window::GetWindow() {
	return this->window;
}

unsigned int Window::GetWidth() {
	return width;
}

unsigned int Window::GetHeight() {
	return height;
}

void FrameBufferSizeChangeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

