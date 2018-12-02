#include "Texture.h"
#include "BMPLoader.h"
#include <glew.h>
#include "GLFW\glfw3.h"

Texture::Texture(Renderer * rendererPtr, const char * imagepath, float massToSet, int frameWidth, int frameHeight, int rows, int columns) : Shape(rendererPtr)
{
	int initialFrameID = 5;
	float x = 0;
	float y = 0;

	texture = BMPLoader::LoadBMP(imagepath, frameWidth, frameHeight, rows, columns, minU, maxU, minV, maxV, initialFrameID, x, y);

	mass = massToSet;
	bbox = new BoundingBox("gB", this, false);
	bbox->isStatic = true;
	bcircle = new BoundingCircle("gB");
	vertexCount = 4;

	//testAnimation = new Animation(this, initialFrameID, 47);

	g_vertex_buffer_data = new float[vertexCount * 3]
	{
		50.0f,50.0f, 0.0f,
		-50.0f,50.0f, 0.0f,
		50.0f, -50.0f, 0.0f,
		-50.0f, -50.0f,0.0f,
	};

	float laco[] =
	{ 
		0.1667,0.9062,
		0,0.9062,
		0.1667, 0.7812,
		0,0.7812
	};

	g_uv_buffer_data = new float[vertexCount * 2];
	g_uv_buffer_data = laco;

	/*g_uv_buffer_data = new float[vertexCount*2]
	{
		maxU, maxV,
		minU, maxV,
		maxU, minV,
		minU, minV,
	};
	*/
	vertexBuffer = renderer->GenBuffer(sizeof(float)*vertexCount * 3, g_vertex_buffer_data);
	uvBuffer = renderer->GenUVBuffer(sizeof(float)*vertexCount * 2, g_uv_buffer_data);
}


Texture::~Texture()
{
	renderer->DestroyBuffer(vertexBuffer);
	renderer->DestroyBuffer(uvBuffer);
	delete[] g_vertex_buffer_data;
	delete[] g_uv_buffer_data;
	delete bbox;
	delete bcircle;
}

void Texture::Draw()
{
	renderer->LoadIdentityMatrix();
	renderer->SetModelMatrix(model);
	bbox->UpdateBoundingBoxModel(100.0f, 100.0f, vectorPosition, mass);
	//bcircle->UpdateBoundingCircleModel(1.0f, vectorPosition, mass);

	if (material != nullptr)
	{
		material->Bind();
		material->SetMatrixProperty(renderer->GetMVP());
		material->SetTextureProperty();
	}


	renderer->BindTexture(texture);


	renderer->EnableAttributes(0);
	renderer->EnableAttributes(1);
	renderer->BindBuffer(vertexBuffer, 0);
	renderer->BindUVBuffer(uvBuffer, 1);
	renderer->DrawBuffer(vertexCount);

	renderer->DisableAttributes(0);
	renderer->DisableAttributes(1);
}
