#include "Texture.h"
#include "BMPLoader.h"
#include <glew.h>
#include "GLFW\glfw3.h"

Texture::Texture(
	Renderer * renderer,
	const char * imagepath,
	float massToSet,
	int frameWidth,
	int frameHeight,
	int initialRow,
	int initialColumn) : Shape(renderer)
{
	int initialFrameID = 5;
	float x = 0;
	float y = 0;

	texture = BMPLoader::LoadBMP(
		imagepath,
		frameWidth,
		frameHeight,
		initialRow,
		initialColumn, /*minU, maxU, minV, maxV, initialFrameID, x, y*/
		spritesheetWidth,
		spritesheetHeight);

	animationSpeed = 0.5f;
	mass = massToSet;
	bbox = new BoundingBox("gB", this, false);
	//bbox->isStatic = true;
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

	g_uv_buffer_data = new float[vertexCount * 2];

	testAnimation = new Animation(this,
		frameWidth,
		frameHeight,
		spritesheetWidth,
		spritesheetHeight,
		g_uv_buffer_data,
		vertexCount * 2,
		animationSpeed,
		initialRow,
		initialColumn);

	/*g_uv_buffer_data = new float[vertexCount*2]
	{
		0.1667f, 0.9062,
		0.0f, 0.9062f,
		0.1667f, 0.7812f,
		0.0f, 0.7812f,
	};*/
	
	//testAnimation->AddFrame(1, 1);

	/*
	testAnimation->AddFrame(2, 1);
	testAnimation->AddFrame(3, 1);
	testAnimation->AddFrame(4, 1);
	testAnimation->AddFrame(5, 1);
	testAnimation->AddFrame(6, 1);
	testAnimation->AddFrame(7, 1);
	testAnimation->AddFrame(8, 1);
	*/
	vertexBuffer = renderer->GenBuffer(sizeof(float)*vertexCount * 3, g_vertex_buffer_data);
	uvBuffer = renderer->GenUVBuffer(sizeof(float)*vertexCount * 2, g_uv_buffer_data);

	cout << "maxU del primero " << testAnimation->frameList->front()->minU << endl;
	cout << "maxU del ultimo " << testAnimation->frameList->back()->minU << endl;
}

void Texture::UpdateDT(double & deltaTime)
{
	dt = deltaTime;
}

Texture::~Texture()
{
	renderer->DestroyBuffer(vertexBuffer);
	renderer->DestroyBuffer(uvBuffer);
	delete[] g_vertex_buffer_data;
	delete[] g_uv_buffer_data;
	delete bbox;
	delete bcircle;
	delete testAnimation;
}

void Texture::Draw()
{
	renderer->LoadIdentityMatrix();
	renderer->SetModelMatrix(model);
	bbox->UpdateBoundingBoxModel(100.0f, 100.0f, vectorPosition, mass);
	testAnimation->Update(dt);
	uvBuffer = renderer->GenUVBuffer(sizeof(float)*vertexCount * 2, g_uv_buffer_data);

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
