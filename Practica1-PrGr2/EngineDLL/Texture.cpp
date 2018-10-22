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
		1.0f,1.0f, 0.0f,
		-1.0f,1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f,0.0f,
	};

	g_uv_buffer_data = new float[vertexCount*2]
	{
		0.000059f, 1.0f - 0.000004f,
		0.000103f, 1.0f - 0.336048f,
		0.335973f, 1.0f - 0.335903f,
		1.000023f, 1.0f - 0.000013f,
	};

	vertexBuffer = renderer->GenBuffer(sizeof(float)*vertexCount * 3, g_vertex_buffer_data);
	uvBuffer = renderer->GenUVBuffer(sizeof(float)*vertexCount * 3, g_uv_buffer_data);
}


Texture::~Texture()
{
	renderer->DestroyBuffer(vertexBuffer);
	renderer->DestroyBuffer(uvBuffer);
	delete[] g_vertex_buffer_data;
	delete[] g_uv_buffer_data;
}

void Texture::Draw()
{
	renderer->LoadIdentityMatrix();
	renderer->SetModelMatrix(model);

	if (material != nullptr)
	{
		material->Bind();
		material->SetMatrixProperty(renderer->GetMVP());
		material->SetTextureProperty(renderer->GetMVP());
	}

	renderer->BindTexture(textureID);
	renderer->EnableAttributes(0);
	renderer->EnableAttributes(1);
	renderer->BindBuffer(vertexBuffer, 0);
	renderer->BindColorBuffer(uvBuffer, 1);
	renderer->DrawBuffer(vertexCount);
}
