#include "Rectangle.h"


Rectangle::Rectangle(Renderer* rendererPtr, float massToSet) : Shape(rendererPtr)
{
	mass = massToSet;
	bbox = new BoundingBox("gA", this, false);
	//bcircle = new BoundingCircle("gA");
	vertexCount = 4;

	g_vertex_buffer_data = new float[vertexCount * 3]
	{
		50.0f,50.0f, 0.0f,
		-50.0f,50.0f, 0.0f,
		50.0f, -50.0f, 0.0f,
		-50.0f, -50.0f,0.0f,
	};


	g_color_buffer_data = new float[vertexCount * 3]
	{
		0.344f,0.255f,0.666f,
		0.457f,0.432f,0.645f,
		0.101f,0.846f,0.222f,
		0.333f,0.512f,0.410f,
	};

	vertexBuffer = renderer->GenBuffer(sizeof(float)*vertexCount * 3, g_vertex_buffer_data);
	colorBuffer = renderer->GenColorBuffer(sizeof(float)*vertexCount * 3, g_color_buffer_data);
}


Rectangle::~Rectangle()
{
	renderer->DestroyBuffer(vertexBuffer);
	renderer->DestroyBuffer(colorBuffer);
	delete[] g_vertex_buffer_data;
	delete[] g_color_buffer_data;
	delete bbox;
	//delete bcircle;
}

void Rectangle::Draw()
{
	renderer->LoadIdentityMatrix();
	renderer->SetModelMatrix(model);
	bbox->UpdateBoundingBoxModel(100.0f, 100.0f, vectorPosition, mass);
	//bcircle->UpdateBoundingCircleModel(1.0f, vectorPosition);

	if (material != nullptr)
	{
		material->Bind();
		material->SetMatrixProperty(renderer->GetMVP());
	}

	renderer->EnableAttributes(0);
	renderer->BindBuffer(vertexBuffer, 0);
	renderer->EnableAttributes(1);
	renderer->BindColorBuffer(colorBuffer, 1);
	renderer->DrawBuffer(vertexCount);
	
	renderer->DisableAttributes(0);
	renderer->DisableAttributes(1);
}