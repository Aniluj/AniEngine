#include "MeshData.h"



MeshData::MeshData(vector<Vertex> vertices, vector<unsigned int> indices, Renderer * rendererPtr)
{
	vertex_buffer_data = new vector<Vertex>(vertices);
	this->indices = new vector<unsigned int>(indices);
	renderer = rendererPtr;

	SetUpMeshData();
}

MeshData::MeshData()
{

}

void MeshData::SetUpMeshData()
{
	vertexBuffer = renderer->GenBuffer(sizeof(Vertex) * vertex_buffer_data->size(), &vertex_buffer_data->at(0));
	//cout << "vertex buffer size: " << sizeof(Vertex) * vertex_buffer_data->size() << endl;
	elementBuffer = renderer->GenElementBuffer(sizeof(unsigned int) * indices->size(), &indices[0]);
	material = Material::CreateMaterial(
										"Shaders/TransformVertexShader.txt",
										"Shaders/ColorFragmentShader.txt");
}

void MeshData::Draw(glm::mat4 & model)
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

	//renderer->EnableAttributes(1);
	//renderer->NormalVertexAttrib(1);

	renderer->BindElementBuffer(elementBuffer);
	renderer->DrawElementBuffer(indices->size());

	renderer->DisableAttributes(0);
}

MeshData::~MeshData()
{
	renderer->DestroyBuffer(vertexBuffer);
	renderer->DestroyBuffer(elementBuffer);
	delete vertex_buffer_data;
	delete indices;
	delete material;
	//delete g_vertex_buffer_data;
}
