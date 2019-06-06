#pragma once

#include "Component.h"
#include "MeshData.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class ENGINEDLL_API MeshComponent : Component
{
private:
	int counter;
	vector<MeshData*> meshesData;
	Renderer * renderer;
	glm::mat4 * model;
public:
	MeshComponent();
	~MeshComponent();

	void Start(const char * componentName, const char* path, const char* texturePath, Renderer* rendererPtr, glm::mat4 & modelRef);
	void LoadModel(string path, string texturePath);
	void ProcessNode(aiNode *node, const aiScene *scene, string texturePath);
	MeshData* ProcessMesh(aiMesh *mesh, const aiScene *scene, string texturePath);
	void Draw() override;
	void Update() override;
	string directory;
};

