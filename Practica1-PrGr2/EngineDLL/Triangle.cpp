#include "glew.h"
#include "Triangle.h"



Triangle::Triangle(Renderer * renderer) : Entity(renderer)
{
	g_vertex_buffer_data = new float[9]
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	renderer->GenBuffer(sizeof(float) * vertexCount * 3, g_vertex_buffer_data);
}


Triangle::~Triangle()
{
	delete[] g_vertex_buffer_data;
}


void Triangle::Draw()
{
	renderer->DrawBuffer(vertexBuffer, vertexCount);
}
