#include "Cube.h"



Cube::Cube(Renderer * rendererPtr) : Mesh(rendererPtr)
{
	vertexCount = 3;

	/*g_vertex_buffer_data = new float[vertexCount * 36]
	{
		-50.0f,-50.0f,-50.0f, // triangle 1 : begin
		-50.0f,-50.0f, 50.0f,
		-50.0f, 50.0f, 50.0f, // triangle 1 : end
		50.0f, 50.0f,-50.0f, // triangle 2 : begin
		-50.0f,-50.0f,-50.0f,
		-50.0f, 50.0f,-50.0f, // triangle 2 : end
		50.0f,-50.0f, 50.0f,
		-50.0f,-50.0f,-50.0f,
		50.0f,-50.0f,-50.0f,
		50.0f, 50.0f,-50.0f,
		50.0f,-50.0f,-50.0f,
		-50.0f,-50.0f,-50.0f,
		-50.0f,-50.0f,-50.0f,
		-50.0f, 50.0f, 50.0f,
		-50.0f, 50.0f,-50.0f,
		50.0f,-50.0f, 50.0f,
		-50.0f,-50.0f, 50.0f,
		-50.0f,-50.0f,-50.0f,
		-50.0f, 50.0f, 50.0f,
		-50.0f,-50.0f, 50.0f,
		50.0f,-50.0f, 50.0f,
		50.0f, 50.0f, 50.0f,
		50.0f,-50.0f,-50.0f,
		50.0f, 50.0f,-50.0f,
		50.0f,-50.0f,-50.0f,
		50.0f, 50.0f, 50.0f,
		50.0f,-50.0f, 50.0f,
		50.0f, 50.0f, 50.0f,
		50.0f, 50.0f,-50.0f,
		-50.0f, 50.0f,-50.0f,
		50.0f, 50.0f, 50.0f,
		-50.0f, 50.0f,-50.0f,
		-50.0f, 50.0f, 50.0f,
		50.0f, 50.0f, 50.0f,
		-50.0f, 50.0f, 50.0f,
		50.0f,-50.0f, 50.0f
	};*/

	g_vertex_buffer_data = new float[vertexCount * 8]
	{
		// Front
		-50.0, -50.0, 50.0,
		50.0, -50.0, 50.0,
		50.0, 50.0, 50.0,
		-50.0, 50.0, 50.0,
		// Back
		-50.0, -50.0, -50.0,
		50.0, -50.0, -50.0,
		50.0, 50.0, -50.0,
		-50.0, 50.0, -50.0,
	};

	g_color_buffer_data = new float[vertexCount * 36]
	{
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};

	vector<unsigned int> indices {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	vertexBuffer = renderer->GenBuffer(vertexCount * 8 * sizeof(float), g_vertex_buffer_data);
	//colorBuffer = renderer->GenBuffer(vertexCount * 36 * sizeof(float), g_color_buffer_data);
	elementBuffer = renderer->GenElementBuffer(sizeof(unsigned int) * indices.size(), indices[0]);
}


Cube::~Cube()
{
	delete[] g_vertex_buffer_data;
	//delete[] g_color_buffer_data;
	//delete[] indices;

	renderer->DestroyBuffer(vertexBuffer);
	//renderer->DestroyBuffer(colorBuffer);
	renderer->DestroyBuffer(elementBuffer);
}

void Cube::Draw()
{
	renderer->LoadIdentityMatrix();
	renderer->SetModelMatrix(model);

	if (material != nullptr)
	{
		material->Bind();
		material->SetMatrixProperty(renderer->GetMVP());
	}

	renderer->EnableAttributes(0);
	//renderer->EnableAttributes(1);
	renderer->BindBuffer(vertexBuffer, 0);
	//renderer->BindColorBuffer(colorBuffer, 1);
	renderer->BindElementBuffer(elementBuffer);
	renderer->DrawElementBuffer(vertexCount * 12);

	renderer->DisableAttributes(0);
	//renderer->DisableAttributes(1);
}
