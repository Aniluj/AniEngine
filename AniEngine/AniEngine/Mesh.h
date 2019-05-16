#pragma once
#include "Entity.h"
#include "MeshData.h"

using namespace std;

class ENGINEDLL_API Mesh : public Entity
{
protected:
	//unsigned int * indices;
	MeshData* meshData;

	int vertexCount;
public:
	Mesh(Renderer* rendererPtr);
	~Mesh();
	void Draw() override;
};

