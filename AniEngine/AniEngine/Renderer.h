#pragma once

#include "Exports.h"
#include "Window.h"
#include <iostream>
//#include "glm\glm.hpp"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\glm.hpp>

using namespace std;

class ENGINEDLL_API Renderer
{
private:
	Window* window;
	unsigned int vertexArrayID;

	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 MVP;
public:
	Renderer();
	~Renderer();
	bool Start(Window* windowPtr);
	bool Stop();
	void ClearColor(float r, float g, float b, float a);
	void ClearScreen();
	void SwapBuffer();
	//void DrawBuffer(unsigned int vertexBuffer, unsigned int vertexCount);
	void DrawBuffer(int vertexCount);
	void DestroyBuffer(unsigned int buffer);
	unsigned int GenBuffer(unsigned int size, float * g_vertex_buffer_data);
	unsigned int GenColorBuffer(unsigned int size, float * g_color_buffer_data);
	unsigned int GenUVBuffer(unsigned int size, float * g_uv_buffer_data);
	void EnableAttributes(unsigned int attributeId);
	void BindBuffer(unsigned int vertexBuffer, unsigned int attributeId);
	void DisableAttributes(unsigned int attributeId);
	void LoadIdentityMatrix();
	void SetModelMatrix(glm::mat4 model);
	void BindColorBuffer(unsigned int colorBuffer, unsigned int attributebID);
	void BindUVBuffer(unsigned int uvBuffer, unsigned int attributebID);
	void BindTexture(unsigned int textureID);
	void SetMVP();

	glm::mat4& GetMVP();
};