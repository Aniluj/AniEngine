#pragma once

#include "Exports.h"
#include <vector>

using namespace std;

class ENGINEDLL_API MeshData
{
public:
	MeshData();
	~MeshData();

	vector<unsigned int>* indices;
	float * g_vertex_buffer_data;
	float * g_uv_buffer_data;
};

