#pragma once

#include "Exports.h"
#include "Renderer.h"
#include "Material.h"
#include <glm/glm.hpp>
#include <vector>

using namespace std;

struct Vertex
{
	// position
	glm::vec3 Position;
	/*
	// normal
	glm::vec3 Normal;
	
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
	*/
};

/*struct Texture
{
	unsigned int id;
	string type;
	string path;
};*/

class ENGINEDLL_API MeshData
{
private:
	Renderer * renderer;
	Material * material;
public:
	MeshData(vector<Vertex> vertices,vector<unsigned int> indices, Renderer * rendererPtr);
	MeshData();
	void SetUpMeshData();
	void Draw(glm::mat4 & model);
	~MeshData();

	unsigned int vertexBuffer;
	unsigned int elementBuffer;
	unsigned int uvBuffer;
	vector<unsigned int>* indices;
	vector<Vertex>* vertex_buffer_data;

	//float * g_vertex_buffer_data;
	//float * g_uv_buffer_data;
};

