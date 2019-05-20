#pragma once


#include "Entity.h"
#include "MeshData.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

using namespace std;

class ENGINEDLL_API Mesh : public Entity
{
protected:
	//unsigned int * indices;
	int counter;
	vector<MeshData*> meshesData;
public:
	Mesh(const char* path, Renderer* rendererPtr, const char* texturePath);
	void LoadModel(string path, string texturePath);
	void ProcessNode(aiNode *node, const aiScene *scene, string texturePath);
	MeshData* ProcessMesh(aiMesh *mesh, const aiScene *scene, string texturePath);
	void Draw() override;
	~Mesh();

	string directory;
};

