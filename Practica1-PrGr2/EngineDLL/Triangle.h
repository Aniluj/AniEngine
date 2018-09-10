#pragma once

#include "Entity.h"
#include "Material.h"

class ENGINEDLL_API Triangle : public Entity
{
private:
	unsigned int vertexBuffer;
	float * g_vertex_buffer_data;
	int vertexCount;
	Material material;
public:
	Triangle(Renderer * renderer);
	~Triangle();
	void Draw() override;
};

