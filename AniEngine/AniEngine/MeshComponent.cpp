#include "MeshComponent.h"



MeshComponent::MeshComponent()
{

}

FrustumCullingBoundingBox::FrustumCullingBoundingBox()
{

}

void MeshComponent::Start(
					      const char * componentName,
					      FrustumCullingBoundingBox * FCBoundingBoxPtr,
					      const vector<Vertex> & vertices,
					      const vector<unsigned int> & indices,
					      Renderer * rendererPtr,
					      string texturePath
					     )
{
	Component::Start(componentName);

	FCBoundingBox = FCBoundingBoxPtr;
	renderer = rendererPtr;
	meshData = new MeshData(vertices, indices, rendererPtr, texturePath);
}

void FrustumCullingBoundingBox::UpdateMaxsAndMins()
{
	bBoxVertices[0].x = mins.x;		bBoxVertices[1].x = maxs.x;
	bBoxVertices[0].y = maxs.y;		bBoxVertices[1].y = maxs.y;
	bBoxVertices[0].z = mins.z;		bBoxVertices[1].z = mins.z;
	bBoxVertices[0].w = 1;			bBoxVertices[1].w = 1;

	bBoxVertices[2].x = mins.x;		bBoxVertices[3].x = maxs.x;
	bBoxVertices[2].y = mins.y;		bBoxVertices[3].y = mins.y;
	bBoxVertices[2].z = mins.z;		bBoxVertices[3].z = mins.z;
	bBoxVertices[2].w = 1;			bBoxVertices[3].w = 1;


	bBoxVertices[4].x = mins.x;		bBoxVertices[5].x = maxs.x;
	bBoxVertices[4].y = maxs.y;		bBoxVertices[5].y = maxs.y;
	bBoxVertices[4].z = maxs.z;		bBoxVertices[5].z = maxs.z;
	bBoxVertices[4].w = 1;			bBoxVertices[5].w = 1;

	bBoxVertices[6].x = mins.x;		bBoxVertices[7].x = maxs.x;
	bBoxVertices[6].y = mins.y;		bBoxVertices[7].y = mins.y;
	bBoxVertices[6].z = maxs.z;		bBoxVertices[7].z = maxs.z;
	bBoxVertices[6].w = 1;			bBoxVertices[7].w = 1;
}

void FrustumCullingBoundingBox::CheckMinsAndMax(glm::vec3 newPositionsToCheck)
{
	if (isFirstTimeSet == false)
	{
		//cout << "entro" << endl;
		if (mins.x > newPositionsToCheck.x) {
			mins.x = newPositionsToCheck.x;
		}
		if (maxs.x < newPositionsToCheck.x) {
			maxs.x = newPositionsToCheck.x;
		}

		if (mins.y > newPositionsToCheck.y) {
			mins.y = newPositionsToCheck.y;
		}
		if (maxs.y < newPositionsToCheck.y) {
			maxs.y = newPositionsToCheck.y;
		}

		if (mins.z > newPositionsToCheck.z) {
			mins.z = newPositionsToCheck.z;
		}
		if (maxs.z < newPositionsToCheck.z) {
			maxs.z = newPositionsToCheck.z;
		}
	}
	else
	{
		mins.x = newPositionsToCheck.x;
		mins.y = newPositionsToCheck.y;
		mins.z = newPositionsToCheck.z;

		maxs.x = newPositionsToCheck.x;
		maxs.y = newPositionsToCheck.y;
		maxs.z = newPositionsToCheck.z;

		isFirstTimeSet = false;
	}
}

void MeshComponent::Draw()
{
	Plane * frustumPlanesPtr = renderer->GetFrustumPlanesPtr();

	for (int i = 0; i < 6; i++)
	{
		bool allBehind = true;

		for (int j = 0; j < 8; j++)
		{
			if (renderer->ClassifyPoint(frustumPlanesPtr[i], renderer->GetModelMatrix() * FCBoundingBox->bBoxVertices[j] /** renderer->GetModelMatrix()*/) == POSITIVE)
			{
				//cout << "CHECKEO EN MESH "  << i << "  " << frustumPlanesPtr[i].a << endl;
				allBehind = false;
				break;
			}
		}
		if (allBehind)
		{
			cout << "NO SE DIBUJAAAAAAAAAAAAAAAAAAAAAAAAA" << i << endl;

			return;
		}
	}

	meshData->Draw();
}

FrustumCullingBoundingBox::~FrustumCullingBoundingBox()
{

}

MeshComponent::~MeshComponent()
{

}