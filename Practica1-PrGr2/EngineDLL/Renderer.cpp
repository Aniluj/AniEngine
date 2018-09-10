#include "Renderer.h"
#include <glew.h>
#include <GLFW\glfw3.h>

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
	// Los siguientes comandos le dar�n caracter�sticas especiales al 'vertexbuffer' 
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Darle nuestros v�rtices a  OpenGL.
	glBufferData(GL_ARRAY_BUFFER, size, g_vertex_buffer_data, GL_STATIC_DRAW);

	return vertexbuffer;
}

void Renderer::DrawBuffer(unsigned int vertexBuffer, unsigned int vertexCount)
{
	// 1rst attribute buffer : v�rtices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0,                  // atributo 0. No hay raz�n particular para el 0, pero debe corresponder en el shader.
		3,                  // tama�o
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		0,                    // Paso
		(void*)0            // desfase del buffer
	);
	// Dibujar el tri�ngulo !
	glDrawArrays(GL_TRIANGLES, 0, vertexCount); // Empezar desde el v�rtice 0S; 3 v�rtices en total -> 1 tri�ngulo
	glDisableVertexAttribArray(0);
}

void Renderer::DestroyBuffer(unsigned int vertexBuffer)
{
	glDeleteBuffers(1, &vertexBuffer);
}