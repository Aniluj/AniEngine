#pragma once
#include "Entity.h"
#include "MeshData.h"

using namespace std;

class ENGINEDLL_API Mesh : public Entity
{
protected:
	//unsigned int * indices;
	MeshData* meshData;

	unsigned int vertexBuffer;
	unsigned int elementBuffer;
	unsigned int uvBuffer;

	int vertexCount;
public:
	Mesh(Renderer* rendererPtr);
	~Mesh();
	Material * material;
};

