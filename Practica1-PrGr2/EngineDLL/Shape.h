#pragma once
#include "Entity.h"

class ENGINEDLL_API Shape : public Entity
{
protected:
	unsigned int vertexBuffer;
	unsigned int colorBuffer;
	float * g_vertex_buffer_data;
	float * g_color_buffer_data;
	int vertexCount;
public:
	Material * material;
	Shape(Renderer* rendererPtr);
	~Shape();
};

