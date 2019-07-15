#pragma once

#include "Component.h"
#include "Exports.h"
#include "MeshData.h"

struct FrustumCullingBoundingBox
{
	FrustumCullingBoundingBox();

	bool isFirstTimeSet = true;

	glm::vec4 bBoxVertices[8];
	glm::vec3 mins;
	glm::vec3 maxs;

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

