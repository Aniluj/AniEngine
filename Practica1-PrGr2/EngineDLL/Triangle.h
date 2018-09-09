#pragma once

#include "Entity.h"
#include "Material.h"

class ENGINEDLL_API Triangle : public Entity
{
private:
	int vertexArrayID;
	//const GLfloat g_vertex_buffer_data[] = {
	//	-1.0f, -1.0f, 0.0f,
	//	1.0f, -1.0f, 0.0f,
	//	0.0f,  1.0f, 0.0f,
	//};
	float g_vertex_buffer_data[9] = {
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			0.0f,  1.0f, 0.0f,
		};
	int vertexBuffer;
public:
	Triangle();
	~Triangle();
	void GenerateVertexAray(int id, int &vertexArrayIDRef);
	void GenerateBuffers(int id, int &vertexBufferRef);
	void SetVertexArrayObject();
	void SetBuffer();
	void BindVertexArray(int &vertexArrayID);
	void BindBuffer(int &vertexBufferRef);
	void SetBufferData(float vertexBufferData[]);
	void EnableVertexAttribArray(int index);
	void VertexAttributePointer(int attribNumber, int size, int step, void* bufferGap);
	void DrawArrays(int initialVertex, int totalVertices);
	void DisableVertexAttributeArray(int index);
	void Draw() override;
};

