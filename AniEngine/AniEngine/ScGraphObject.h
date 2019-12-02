#pragma once

#include "Exports.h"
#include "Node.h"
#include "MeshComponentLoader.h"
#include "Renderer.h"

class ENGINEDLL_API ScGraphObject
{
private:
	Renderer * renderer;
	Node * spider;
	Node * M4;
	MeshComponentLoader * M4Mesh;
	MeshComponentLoader * spiderMesh;
public:
	ScGraphObject(Renderer * rendererPtr);
	Node* rootNode;
	~ScGraphObject();
	void Update();
	void Draw();
};

