#include "glew.h"
#include "Triangle.h"



Triangle::Triangle(Renderer * rendererPtr) : Shape(rendererPtr)
{
	vertexCount = 3;

	g_vertex_buffer_data = new float[vertexCount * 3]
	{
		-50.0f, -50.0f, 0.0f,
		50.0f, -50.0f, 0.0f,
		0.0f,  50.0f, 0.0f,
	};

	vertexBuffer = renderer->GenBuffer(sizeof(float) * vertexCount * 3, g_vertex_buffer_data);
}


Triangle::~Triangle()
{
	renderer->DestroyBuffer(vertexBuffer);
	delete[] g_vertex_buffer_data;
}


void Triangle::Draw()
{
	renderer->LoadIdentityMatrix();
	renderer->SetModelMatrix(model);

	if (material != nullptr)
	{
		material->Bind();
		material->SetMatrixProperty(renderer->GetMVP());
	}
	renderer->EnableAttributes(0);
	renderer->BindBuffer(vertexBuffer, 0);
	renderer->DrawBuffer(vertexCount);

	renderer->DisableAttributes(0);
}
