#include <GLFW\glfw3.h>
#include "Window.h"


Window::Window()
{

}

Window::~Window()
{

}

bool Window::Start(const int widthParam,const int heightParam,const char* windowName)
{
	cout << "Window::Start()" << endl;

	width = widthParam;
	height = heightParam;

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

void* Window::GetWindowPtr()
{
	return window;
}

void Window::PollEvents()
{
	glfwPollEvents();
}