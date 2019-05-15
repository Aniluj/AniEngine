#pragma once

#include "Exports.h"
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

struct Texture
{
	unsigned int id;
	string type;
	string path;
};

class ENGINEDLL_API MeshData
{
public:
	MeshData();
	~MeshData();

	vector<unsigned int>* indices;
	float * g_vertex_buffer_data;
	float * g_uv_buffer_data;
};

