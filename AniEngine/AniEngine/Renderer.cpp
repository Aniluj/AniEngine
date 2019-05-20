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

		//projectionMatrix = glm::ortho(0.0f, (float)window->GetWidth(), 0.0f, (float)window->GetHeight(), 0.0f, 100.0f);
		//projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

		SetProjectionMatrixToOrtho(0.0f, (float)window->GetWidth(), 0.0f, (float)window->GetHeight(), 0.1f, 1000.0f);
		SetViewMatrix(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		/*viewMatrix = glm::lookAt(
			glm::vec3(0, 0, 3), 
			glm::vec3(0, 0, 0), 
			glm::vec3(0, 1, 0)  
		);*/

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		cout << "Renderer::Start()" << endl;

		return true;
	}

	return false;
}

void Renderer::SetViewMatrix(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	viewMatrix = glm::lookAt(eye, center, up);
}

void Renderer::SetViewMatrix(glm::mat4 viewMatrixValues)
{
	viewMatrix = viewMatrixValues;
}

void Renderer::SetProjectionMatrixToOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
	typeOfProjection = Ortho;
}

void Renderer::SetProjectionMatrixToOrtho(float left, float right, float bottom, float top)
{
	projectionMatrix = glm::ortho(left, right, bottom, top);
	typeOfProjection = Ortho;
}

void Renderer::SetProjectionMatrixToPerspective(float fovy, float aspect, float zNear, float zFar)
{
	projectionMatrix = glm::perspective(fovy, aspect, zNear, zFar);
	typeOfProjection = Perspective;
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

unsigned int Renderer::GenBuffer(unsigned int size,float * g_vertex_buffer_data)
{

	GLuint vertexbuffer;

	glGenBuffers(1, &vertexbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	glBufferData(GL_ARRAY_BUFFER, size, g_vertex_buffer_data, GL_STATIC_DRAW);

	return vertexbuffer;
}

unsigned int Renderer::GenElementBuffer(unsigned int size, const void * g_element_buffer_data)
{
	GLuint elementbuffer;

	glGenBuffers(1, &elementbuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, g_element_buffer_data, GL_STATIC_DRAW);

	return elementbuffer;
}

void Renderer::DrawBuffer(int vertexCount)
{
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexCount);
}

void Renderer::DrawElementBuffer(int vertexCount)
{
	glDrawElements(
		GL_TRIANGLES,      // mode
		vertexCount,    // count
		GL_UNSIGNED_INT,   // type
		(void*)0           // element array buffer offset
	);
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

void Renderer::BindElementBuffer(unsigned int elementBuffer)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
}

void Renderer::NormalVertexAttrib(unsigned int attributebID)
{
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