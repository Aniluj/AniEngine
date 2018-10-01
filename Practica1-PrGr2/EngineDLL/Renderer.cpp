#include "Renderer.h"
#include <glew.h>
#include "GLFW\glfw3.h"



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

		if(glewInit()!=GLEW_OK)
		{
			return false;
		}

		glGenVertexArrays(1, &vertexArrayID);
		glBindVertexArray(vertexArrayID);

		projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);
		//projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

		viewMatrix = glm::lookAt(
			glm::vec3(0, 0, 3), // Camera is at (0, 0, 3), is World Space
			glm::vec3(0, 0, 0), // Looks at the origin
			glm::vec3(0, 1, 0)  // Head is up to (0, 1, 0)
		);

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

unsigned int Renderer::GenBuffer(unsigned int size, float * g_vertex_buffer_data)
{

	GLuint vertexbuffer;

	glGenBuffers(1, &vertexbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	glBufferData(GL_ARRAY_BUFFER, size, g_vertex_buffer_data, GL_STATIC_DRAW);

	return vertexbuffer;
}

void Renderer::DrawBuffer(int vertexCount)
{
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexCount);
}

void Renderer::DestroyBuffer(unsigned int vertexBuffer)
{
	glDeleteBuffers(1, &vertexBuffer);
}

void Renderer::EnableAttributes(unsigned int attributebID)
{
	glEnableVertexAttribArray(attributebID);
}

void Renderer::BindBuffer(unsigned int vertexBuffer, unsigned int attributebID)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		attributebID,       
		3,                  
		GL_FLOAT,           
		GL_FALSE,           
		0,                  
		(void*)0            
	);
}

void Renderer::DisableAttributes(unsigned int attributeID)
{
	glDisableVertexAttribArray(attributeID);
}

void Renderer::LoadIdentityMatrix()
{
	modelMatrix = glm::mat4(1.0f);

	SetMVP();
}

void Renderer::SetModelMatrix(glm::mat4 model)
{
	modelMatrix = model;

	SetMVP();
}

void Renderer::SetMVP()
{
	MVP = projectionMatrix * viewMatrix * modelMatrix;
}

glm::mat4& Renderer::GetMVP()
{
	return MVP;
}