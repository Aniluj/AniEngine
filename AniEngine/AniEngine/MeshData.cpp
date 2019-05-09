#include "MeshData.h"



MeshData::MeshData()
{
}


MeshData::~MeshData()
{
	delete indices;
	delete g_vertex_buffer_data;
}
