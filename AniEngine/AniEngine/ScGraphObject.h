#pragma once

#include "Exports.h"
#include "Node.h"
#include "MeshComponent.h"
#include "Renderer.h"

class ENGINEDLL_API ScGraphObject
{
private:
	Renderer * renderer;
	Node * spider;
	MeshComponent * M4Mesh;
	MeshComponent * spiderMesh;
public:
	ScGraphObject(Renderer * rendererPtr);
	Node * M4;
	~ScGraphObject();
	void Draw();
};

