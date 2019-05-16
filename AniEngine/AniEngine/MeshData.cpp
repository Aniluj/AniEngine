#include "MeshData.h"



MeshData::MeshData(const vector<Vertex> & vertices,const vector<unsigned int> & indices, Renderer * rendererPtr)
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
	vertexBuffer = renderer->GenBuffer(sizeof(Vertex) * vertex_buffer_data->size(), &vertex_buffer_data[0]);
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

	renderer->BindElementBuffer(elementBuffer);
	renderer->DrawElementBuffer(indices->size());

	renderer->DisableAttributes(0);
}

MeshData::~MeshData()
{
	delete vertex_buffer_data;
	delete indices;
	delete g_vertex_buffer_data;
}
