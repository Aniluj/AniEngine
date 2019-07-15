#pragma once

#include "Component.h"
#include "MeshData.h"
#include "MeshComponent.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class ENGINEDLL_API MeshComponentLoader : public Component
{
private:
	int counter;
	vector<MeshData*> meshesData;
	Renderer * renderer;
public:
	MeshComponentLoader();
	~MeshComponentLoader();

	void Start(const char * componentName, const char* path, const char* texturePath, Renderer* rendererPtr);
	void LoadModel(string path, string texturePath);
	void ProcessNode(aiNode *node, const aiScene *scene, string texturePath);
	MeshData* ProcessMesh(aiMesh *mesh, const aiScene *scene, string texturePath);
	void Draw() override;
	void Update() override;
	string directory;
	FrustumCullingBoundingBox * bBox;
	void DrawBoundingBox();
};

