#pragma once

#include "Exports.h"
#include "Window.h"
#include <iostream>


using namespace std;

class ENGINEDLL_API Renderer
{
private:
	Window* window;
	unsigned int vertexArrayID;
public:
	Renderer();
	~Renderer();
	bool Start(Window* windowPtr);
	bool Stop();
	void ClearColor(float r, float g, float b, float a);
	void ClearScreen();
	void SwapBuffer();
	void DrawBuffer(unsigned int vertexBuffer, unsigned int vertexCount);
	void DestroyBuffer(unsigned int vertexBuffer);
	unsigned int GenBuffer(unsigned int size, float * g_vertex_buffer_data);
};