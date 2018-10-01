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

		cout << "Renderer::Start()" << endl;

		glGenVertexArrays(1, &vertexArrayID);
		glBindVertexArray(vertexArrayID);

		glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

		viewMatrix = glm::lookAt(
			glm::vec3(0, 0, 3), // Camera is at (0, 0, 3), is World Space
			glm::vec3(0, 0, 0), // Looks at the origin
			glm::vec3(0, 1, 0)  // Head is up to (0, 1, 0)
		);

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
	// Identificar el vertex buffer
	GLuint vertexbuffer;
	// Generar un buffer, poner el resultado en el vertexbuffer que acabamos de crear
	glGenBuffers(1, &vertexbuffer);
	// Los siguientes comandos le darán características especiales al 'vertexbuffer' 
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Darle nuestros vértices a  OpenGL.
	glBufferData(GL_ARRAY_BUFFER, size, g_vertex_buffer_data, GL_STATIC_DRAW);

	return vertexbuffer;
}

//void Renderer::DrawBuffer(unsigned int vertexBuffer, unsigned int vertexCount)
//{
//	// 1rst attribute buffer : vértices
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//	glVertexAttribPointer(
//		0,                  // atributo 0. No hay razón particular para el 0, pero debe corresponder en el shader.
//		3,                  // tamaño
//		GL_FLOAT,           // tipo
//		GL_FALSE,           // normalizado?
//		0,                    // Paso
//		(void*)0            // desfase del buffer
//	);
//	// Dibujar el triángulo !
//	glDrawArrays(GL_TRIANGLES, 0, vertexCount); // Empezar desde el vértice 0S; 3 vértices en total -> 1 triángulo
//	glDisableVertexAttribArray(0);
//}

void Renderer::DrawBuffer(int vertexCount)
{
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexCount); // Empezar desde el vértice 0S; 3 vértices en total -> 1 triángulo
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
		attributebID,       // debe corresponder en el shader.
		3,                  // tamaño
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		0,                  // corrimiento
		(void*)0            // desfase del buffer
	);
}

void Renderer::DisableAttributes(unsigned int attributeID)
{
	glDisableVertexAttribArray(attributeID);
}

void Renderer::loadIdentityMatrix()
{
	modelMatrix = glm::mat4(1.0f);

	SetMVP();
}

void Renderer::SetModelMatrix(glm::mat4 model)
{
	modelMatrix = model;

	SetMVP();
}

void Renderer::MultiplyModelMatrix(glm::mat4 model)
{
	modelMatrix *= model;

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