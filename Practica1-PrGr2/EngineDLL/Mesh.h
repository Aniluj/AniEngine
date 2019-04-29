#pragma once
#include "Entity.h"
#include <vector>

using namespace std;

class ENGINEDLL_API Mesh : public Entity
{
protected:
	//vector<unsigned int> indices;

	unsigned int * indices;
	float * g_vertex_buffer_data;
	unsigned int elementBuffer;
	int vertexCount;
public:
	Mesh(Renderer* rendererPtr);
	~Mesh();
};

