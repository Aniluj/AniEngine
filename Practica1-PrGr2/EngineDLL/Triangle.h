#pragma once

#include "Entity.h"
#include "Shape.h"
#include "Material.h"

class ENGINEDLL_API Triangle : public Shape
{
/*private:
	unsigned int vertexBuffer;
	float * g_vertex_buffer_data;
	int vertexCount;*/
public:
	Triangle(Renderer * rendererPtr);
	~Triangle();
	void Draw() override;
};

