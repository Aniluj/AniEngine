#include <GLFW\glfw3.h>
#include "Renderer.h"

Renderer::Renderer()
{

}


Renderer::~Renderer()
{

}

bool Renderer::Start(Window* windowPtr)
{
	if (windowPtr != nullptr)
	{
		window = windowPtr;

		glfwMakeContextCurrent((GLFWwindow*)window->GetWindowPtr());

		cout << "Renderer::Start()" << endl;

		return true;
	}
	return false;
}

bool Renderer::Stop()
{
	cout << "Renderer::Stop()" << endl;

	return true;
}

void Renderer::ClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SwapBuffer()
{
	glfwSwapBuffers((GLFWwindow*)window->GetWindowPtr());
}