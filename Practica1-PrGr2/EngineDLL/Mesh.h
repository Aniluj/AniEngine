#pragma once
#include "Entity.h"
#include <vector>

using namespace std;

class ENGINEDLL_API Mesh : public Entity
{
protected:
	//vector<unsigned int> indices;

	float * g_vertex_buffer_data;
	float * g_color_buffer_data;
	float * g_uv_buffer_data;
	unsigned int * indices;

	unsigned int vertexBuffer;
	unsigned int elementBuffer;
	unsigned int colorBuffer;
	unsigned int uvBuffer;

	int vertexCount;
public:
	Mesh(Renderer* rendererPtr);
	~Mesh();
};

