#include "MeshData.h"



MeshData::MeshData(const vector<Vertex> & vertices,const vector<unsigned int> & indices, Renderer * rendererPtr, string texturePath)
{
	vertex_buffer_data = new vector<Vertex>(vertices);
	this->indices = new vector<unsigned int>(indices);
	texture = new TextureInfoForMeshData();
	texture->path = texturePath;
	texture->id = BMPLoader::LoadBMP(texture->path.c_str());
	renderer = rendererPtr;
	SetUpMeshData();
}

MeshData::MeshData()
{

}

void MeshData::SetUpMeshData()
{
	positions = new float[vertex_buffer_data->size() * 3];
	textureCoords = new float[vertex_buffer_data->size() * 2];
	normals = new float[vertex_buffer_data->size() * 3];

	for (int i = 0; i < vertex_buffer_data->size(); i++)
	{
		positions[i * 3] = vertex_buffer_data->at(i).Position.x;
		positions[i * 3 + 1] = vertex_buffer_data->at(i).Position.y;
		positions[i * 3 + 2] = vertex_buffer_data->at(i).Position.z;
		textureCoords[i * 2] = vertex_buffer_data->at(i).TexCoords.x;
		textureCoords[i * 2 + 1] = vertex_buffer_data->at(i).TexCoords.y;
		normals[i * 3] = vertex_buffer_data->at(i).Normal.x;
		normals[i * 3 + 1] = vertex_buffer_data->at(i).Normal.y;
		normals[i * 3 + 2] = vertex_buffer_data->at(i).Normal.z;
	}

	vertexBuffer = renderer->GenBuffer(sizeof(float) * vertex_buffer_data->size() * 3, positions);
	//cout << "vertex buffer size: " << sizeof(Vertex) * vertex_buffer_data->size() << endl;
	elementBuffer = renderer->GenElementBuffer(sizeof(unsigned int) * indices->size(), &indices->at(0));
	uvBuffer = renderer->GenUVBuffer(sizeof(float) * vertex_buffer_data->size() * 2, textureCoords);
	material = Material::CreateMaterial(
										"Shaders/TextureTransformVertexShader.txt",
										"Shaders/TextureFragmentShader.txt");
}

void MeshData::Draw(glm::mat4 & model)
{
	renderer->LoadIdentityMatrix();
	renderer->SetModelMatrix(model);

	if (material != nullptr)
	{
		material->Bind();
		renderer->BindTexture(texture->id);
		material->SetMatrixProperty(renderer->GetMVP());
		material->SetTextureProperty();
	}

	renderer->EnableAttributes(0);
	renderer->EnableAttributes(1);
	renderer->EnableAttributes(2);

	renderer->BindBuffer(vertexBuffer, 0);

	renderer->BindUVBuffer(uvBuffer, 1);

	renderer->NormalVertexAttrib(2);

	renderer->BindElementBuffer(elementBuffer);

	renderer->DrawElementBuffer(indices->size());

	renderer->DisableAttributes(0);
	renderer->DisableAttributes(1);
	renderer->DisableAttributes(2);
}

MeshData::~MeshData()
{
	renderer->DestroyBuffer(vertexBuffer);
	renderer->DestroyBuffer(elementBuffer);
	renderer->DestroyBuffer(uvBuffer);
	delete positions;
	delete textureCoords;
	delete normals;
	delete vertex_buffer_data;
	delete indices;
	delete material;
	delete texture;
}
