#include "Triangle.h"
#include "glew.h"


Triangle::Triangle()
{

}


Triangle::~Triangle()
{

}

void Triangle::GenerateVertexAray(int id, int &vertexArrayIDRef)
{
	glGenVertexArrays(id, (GLuint*)vertexArrayIDRef);
}

void Triangle::GenerateBuffers(int id, int &vertexBufferRef)
{
	glGenBuffers(id, (GLuint*)vertexBufferRef);
}

void Triangle::SetVertexArrayObject()
{
	GenerateVertexAray(1, vertexArrayID);
	BindVertexArray(vertexArrayID);
}

void Triangle::SetBuffer()
{
	GenerateBuffers(1, vertexBuffer);
	BindBuffer(vertexBuffer);
	SetBufferData(g_vertex_buffer_data);
}

void Triangle::BindVertexArray(int &vertexArrayIDRef)
{
	glBindVertexArray(vertexArrayIDRef);
}

void Triangle::BindBuffer(int &vertexBufferRef)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferRef);
}

void Triangle::SetBufferData(float vertexBufferData[])
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
}

void Triangle::VertexAttributePointer(int attribNumber, int size, int step, void* bufferGap)
{
	glVertexAttribPointer(attribNumber, size, GL_FLOAT, GL_FALSE, step, bufferGap);
}

void Triangle::EnableVertexAttribArray(int index)
{
	glEnableVertexAttribArray(index);
}

void Triangle::DrawArrays(int initialVertex, int totalVertices)
{
	glDrawArrays(GL_TRIANGLES, initialVertex, totalVertices);
}

void Triangle::DisableVertexAttributeArray(int index)
{
	glDisableVertexAttribArray(index);
}

void Triangle::Draw()
{
	EnableVertexAttribArray(0);
	BindBuffer(vertexBuffer);
	VertexAttributePointer(0, 3, 0, (void*)0);
	DrawArrays(0, 3);
	DisableVertexAttributeArray(0);
}
