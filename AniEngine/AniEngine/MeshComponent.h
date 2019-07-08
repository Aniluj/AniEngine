#pragma once

#include "Component.h"
#include "MeshData.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

struct BoundingBoxForDrawing
{
	BoundingBoxForDrawing();

	bool isFirstTimeSet = true;

	float minX;
	float minY;
	float minZ;

	float maxX;
	float maxY;
	float maxZ;

	glm::vec4 bBoxVertices[8];

	void CheckMinsAndMax(glm::vec3 newPositionsToCheck);

	~BoundingBoxForDrawing();
};

class ENGINEDLL_API MeshComponent : public Component
{
private:
	int counter;
	vector<MeshData*> meshesData;
	Renderer * renderer;
public:
	MeshComponent();
	~MeshComponent();

	void Start(const char * componentName, const char* path, const char* texturePath, Renderer* rendererPtr);
	void LoadModel(string path, string texturePath);
	void ProcessNode(aiNode *node, const aiScene *scene, string texturePath);
	MeshData* ProcessMesh(aiMesh *mesh, const aiScene *scene, string texturePath);
	void Draw() override;
	void Update() override;
	string directory;
	BoundingBoxForDrawing * bBox;
};

