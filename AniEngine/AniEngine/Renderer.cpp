#include "Renderer.h"
#include <glew.h>
#include "GLFW\glfw3.h"



Renderer::Renderer()
{

}


Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &vertexArrayID);
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

		projectionMatrix = glm::ortho(0.0f, (float)window->GetWidth(), 0.0f, (float)window->GetHeight(), 0.0f, 1.0f);
		//projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

		viewMatrix = glm::lookAt(
			glm::vec3(0.0f, 0.0f, 1000.0f),
			glm::vec3(0, 0, 0), 
			glm::vec3(0, 1, 0)  
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

void Renderer::DrawBuffer(PrimitiveType primitive, int vertexCount)
{
	glDrawArrays(primitive, 0, vertexCount);
}

void Renderer::DestroyBuffer(unsigned int buffer)
{
	glDeleteBuffers(1, &buffer);
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

void Renderer::BindColorBuffer(unsigned int colorBuffer, unsigned int attributebID)
{
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(
		attributebID,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
}

void Renderer::BindUVBuffer(unsigned int uvBuffer, unsigned int attributebID)
{
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(
		attributebID,                     // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
}

void Renderer::BindTexture(unsigned int textureID)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

unsigned int Renderer::GenColorBuffer(unsigned int size, float * g_color_buffer_data)
{
	GLuint colorbuffer;

	glGenBuffers(1, &colorbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);

	glBufferData(GL_ARRAY_BUFFER, size, g_color_buffer_data, GL_STATIC_DRAW);

	return colorbuffer;
}

unsigned int Renderer::GenUVBuffer(unsigned int size, float * g_uv_buffer_data)
{
	GLuint uvbuffer;

	glGenBuffers(1, &uvbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);

	glBufferData(GL_ARRAY_BUFFER, size, g_uv_buffer_data, GL_STATIC_DRAW);

	return uvbuffer;
}

void Renderer::DisableAttributes(unsigned int attributeID)
{
	glDisableVertexAttribArray(attributeID);
}

void Renderer::EnableBlend() const
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::DisableBlend() const
{
	glDisable(GL_BLEND);
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

void Renderer::UpdateView(float x, float y)
{
	glm::vec3 newCameraPos(x, y, 1.0f);

	viewMatrix = glm::lookAt(newCameraPos, glm::vec3(newCameraPos.x, newCameraPos.y, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

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

Window* Renderer::GetRenderWindow()
{
	return window;
}