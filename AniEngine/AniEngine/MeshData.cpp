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
	float * positions = new float[vertex_buffer_data->size() * 3];

	for (int i = 0; i < vertex_buffer_data->size(); i++)
	{
		positions[i * 3] = vertex_buffer_data->at(i).Position.x;
		positions[i * 3 + 1] = vertex_buffer_data->at(i).Position.y;
		positions[i * 3 + 2] = vertex_buffer_data->at(i).Position.z;
	}

	vertexBuffer = renderer->GenBuffer(sizeof(float) * vertex_buffer_data->size() * 3, positions);
	//cout << "vertex buffer size: " << sizeof(Vertex) * vertex_buffer_data->size() << endl;
	elementBuffer = renderer->GenElementBuffer(sizeof(unsigned int) * indices->size(), &indices->at(0));
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
