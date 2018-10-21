#include "Texture.h"
#include "BMPLoader.h"
#include <glew.h>
#include "GLFW\glfw3.h"

Texture::Texture(Renderer * rendererPtr, const char * imagepath) : Shape(rendererPtr)
{
	textureID = BMPLoader::LoadBMP(imagepath);
	vertexCount = 4;

	g_vertex_buffer_data = new float[vertexCount * 3]
	{
		1.0f,1.5f, 0.0f,
		-1.0f,1.5f, 0.0f,
		1.0f, -1.5f, 0.0f,
		-1.0f, -1.5f,0.0f,
	};

	g_uv_buffer_data = new float[vertexCount*2]
	{
		0.000059f, 1.0f - 0.000004f,
		0.000103f, 1.0f - 0.336048f,
		1.000023f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
	};

	vertexBuffer = renderer->GenBuffer(sizeof(float)*vertexCount * 3, g_vertex_buffer_data);
	uvBuffer = renderer->GenUVBuffer(sizeof(float)*vertexCount * 3, g_uv_buffer_data);
}


Texture::~Texture()
{

}

void Texture::Draw()
{
	renderer->LoadIdentityMatrix();
	renderer->SetModelMatrix(model);

	if (material != nullptr)
	{
		material->Bind();
		material->SetMatrixProperty(renderer->GetMVP());
	}

	BindTexture();
	renderer->EnableAttributes(0);
	renderer->EnableAttributes(1);
	renderer->BindBuffer(vertexBuffer, 0);
	renderer->BindColorBuffer(uvBuffer, 1);
	renderer->DrawBuffer(vertexCount);
}

void Texture::BindTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}
