#pragma once

#include "Exports.h"
#include "Window.h"
#include <iostream>
#include <vector>
//#include "glm\glm.hpp"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\glm.hpp>
#include "Plane.h"

using namespace std;

enum  ProjectionType
{
	Ortho,
	Perspective
};

enum Halfspace
{
	NEGATIVE = -1,
	ON_PLANE = 0,
	POSITIVE = 1
};

class ENGINEDLL_API Renderer
{
private:
	Window* window;
	unsigned int vertexArrayID;

	glm::mat4 combinedViewAndProjectionMatrix;
	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 MVP;
	ProjectionType typeOfProjection;

	Plane * frustumPlanes;

	Plane * leftClippingPlane;
	Plane * rightClippingPlane;
	Plane * topClippingPlane;
	Plane * bottomClippingPlane;
	Plane * nearClippingPlane;
	Plane * farClippingPlane;
public:
	Renderer();
	~Renderer();

	glm::mat4 projectionMatrix;

	bool Start(Window* windowPtr);
	bool Stop();
	void ClearColor(float r, float g, float b, float a);
	void ClearScreen();
	void SwapBuffer();
	//void DrawBuffer(unsigned int vertexBuffer, unsigned int vertexCount);
	void DrawBuffer(int vertexCount);
	void DrawElementBuffer(int vertexCount);
	void DestroyBuffer(unsigned int buffer);

	unsigned int GenBuffer(unsigned int size, float * g_vertex_buffer_data);
	unsigned int GenColorBuffer(unsigned int size, float * g_color_buffer_data);
	unsigned int GenUVBuffer(unsigned int size, float * g_uv_buffer_data);
	unsigned int GenElementBuffer(unsigned int size, const void * g_element_buffer_data);

	void EnableAttributes(unsigned int attributeId);
	void BindBuffer(unsigned int vertexBuffer, unsigned int attributeId);
	void NormalVertexAttrib(unsigned int attributebID);
	void DisableAttributes(unsigned int attributeId);
	void LoadIdentityMatrix();
	void SetModelMatrix(glm::mat4 model);
	void BindColorBuffer(unsigned int colorBuffer, unsigned int attributebID);
	void BindUVBuffer(unsigned int uvBuffer, unsigned int attributebID);
	void BindTexture(unsigned int textureID);
	void BindElementBuffer(unsigned int elementBuffer);

	void SetProjectionMatrixToOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
	void SetProjectionMatrixToOrtho(float left, float right, float bottom, float top);
	void SetProjectionMatrixToPerspective(float fovy, float aspect, float zNear, float zFar);
	void SetViewMatrix(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
	void SetViewMatrix(glm::mat4 viewMatrixValues);
	void SetFrustumPlanes();

	Halfspace ClassifyPoint(const Plane & plane, const glm::vec4 & vector);

	void SetMVP();
	void MultiplyModel(glm::mat4 matrix);
	void MultiplyViewAndProjection();

	glm::mat4& GetMVP();
	glm::mat4 GetModelMatrix();
	Plane * GetFrustumPlanesPtr();
	void NormalizePlanes(Plane & plane);
};