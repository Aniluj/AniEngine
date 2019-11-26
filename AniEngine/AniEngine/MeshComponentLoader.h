#pragma once

#include "Component.h"
#include "MeshData.h"
#include "MeshComponent.h"
#include "Node.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class ENGINEDLL_API MeshComponentLoader : public Component
{
private:
	int counter;
	vector<MeshData*> meshesData;
	Renderer * renderer;
	Node * rootNode;
public:
	MeshComponentLoader();
	~MeshComponentLoader();

	void Start(const char * componentName, Node * rootNodePtr,const char* path, const char* texturePath, Renderer* rendererPtr);
	void LoadModel(string path, string texturePath);
	void ProcessNode(aiNode *node, const aiScene *scene, string texturePath);
	void ProcessMesh(aiMesh *mesh, const aiScene *scene, string texturePath);
	void Draw() override;
	void Update() override;
	string directory;
	FrustumCullingBoundingBox * FCBoundingBox;
};

