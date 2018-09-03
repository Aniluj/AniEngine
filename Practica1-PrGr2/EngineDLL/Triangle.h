#pragma once

#include "Entity.h"
#include "Material.h"

class ENGINEDLL_API Triangle : public Entity
{
private:
	GLuint* vertexArrayID;
	GLfloat g_vertex_buffer_data[];
public:
	Triangle();
	~Triangle();
	void GenerateVertexAray(int id, GLuint* vertexArrayID);
	void BindVertexArray(GLuint* vertexArrayID);
	void SetVertexBufferData(GLfloat vertexBufferData[]);
protected:
	void Draw() override;
};

