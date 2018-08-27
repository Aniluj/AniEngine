#include <GLFW\glfw3.h>
#include "Window.h"

Window::Window()
{
}


Window::~Window()
{
}

bool Window::Start(const int width,const int height,const char* windowName)
{
	cout << "Window::Start()" << endl;

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return false;
	}

	window = glfwCreateWindow(width, height, windowName, NULL, NULL);

	return true;
}

bool Window::Stop()
{
	cout << "Window::Stop()" << endl;

	if (window != NULL)
	{
		glfwDestroyWindow((GLFWwindow*)window);
	}

	glfwTerminate();

	return true;
}

bool Window::ShouldClose()
{
	if (window)
	{
		return glfwWindowShouldClose((GLFWwindow*)window);
	}

	return true;
}

void Window::PollEvents()
{
	glfwPollEvents();
}
