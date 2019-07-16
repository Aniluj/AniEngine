#pragma once

#include "Component.h"
#include "Exports.h"
#include "MeshData.h"
#include "Material.h"

struct FrustumCullingBoundingBox
{
	FrustumCullingBoundingBox();

	bool isFirstTimeSet = true;

	glm::vec4 bBoxVertices[8];
	glm::vec3 min;
	glm::vec3 max;

	void CheckMinsAndMax(glm::vec3 newPositionsToCheck);
	void UpdateMaxsAndMins();

	~FrustumCullingBoundingBox();
};

class ENGINEDLL_API MeshComponent : public Component
{
private:
	MeshData * meshData;
	FrustumCullingBoundingBox * FCBoundingBox;
	Renderer * renderer;
	int counter = 0;
public:
	MeshComponent();

	void Start(
			   const char * componentName,
			   FrustumCullingBoundingBox * FCBoundingBoxPtr,
			   const vector<Vertex> & vertices,
			   const vector<unsigned int> & indices,
			   Renderer * rendererPtr,
			   string texturePath
			   );

	void Draw() override;
	void Update() override;

	~MeshComponent();
};

