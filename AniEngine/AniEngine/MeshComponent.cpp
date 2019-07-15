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
	componentType = MeshType;

	FCBoundingBox = FCBoundingBoxPtr;
	renderer = rendererPtr;
	meshData = new MeshData(vertices, indices, rendererPtr, texturePath);
}

void FrustumCullingBoundingBox::UpdateMaxsAndMins()
{
	bBoxVertices[0].x = min.x;		bBoxVertices[1].x = max.x;
	bBoxVertices[0].y = max.y;		bBoxVertices[1].y = max.y;
	bBoxVertices[0].z = min.z;		bBoxVertices[1].z = min.z;
	bBoxVertices[0].w = 1;			bBoxVertices[1].w = 1;

	bBoxVertices[2].x = min.x;		bBoxVertices[3].x = max.x;
	bBoxVertices[2].y = min.y;		bBoxVertices[3].y = min.y;
	bBoxVertices[2].z = min.z;		bBoxVertices[3].z = min.z;
	bBoxVertices[2].w = 1;			bBoxVertices[3].w = 1;


	bBoxVertices[4].x = min.x;		bBoxVertices[5].x = max.x;
	bBoxVertices[4].y = max.y;		bBoxVertices[5].y = max.y;
	bBoxVertices[4].z = max.z;		bBoxVertices[5].z = max.z;
	bBoxVertices[4].w = 1;			bBoxVertices[5].w = 1;

	bBoxVertices[6].x = min.x;		bBoxVertices[7].x = max.x;
	bBoxVertices[6].y = min.y;		bBoxVertices[7].y = min.y;
	bBoxVertices[6].z = max.z;		bBoxVertices[7].z = max.z;
	bBoxVertices[6].w = 1;			bBoxVertices[7].w = 1;
}

void FrustumCullingBoundingBox::CheckMinsAndMax(glm::vec3 newPositionsToCheck)
{
	if (isFirstTimeSet == false)
	{
		//cout << "entro" << endl;
		if (min.x > newPositionsToCheck.x) {
			min.x = newPositionsToCheck.x;
		}
		if (max.x < newPositionsToCheck.x) {
			max.x = newPositionsToCheck.x;
		}

		if (min.y > newPositionsToCheck.y) {
			min.y = newPositionsToCheck.y;
		}
		if (max.y < newPositionsToCheck.y) {
			max.y = newPositionsToCheck.y;
		}

		if (min.z > newPositionsToCheck.z) {
			min.z = newPositionsToCheck.z;
		}
		if (max.z < newPositionsToCheck.z) {
			max.z = newPositionsToCheck.z;
		}
	}
	else
	{
		min.x = newPositionsToCheck.x;
		min.y = newPositionsToCheck.y;
		min.z = newPositionsToCheck.z;

		max.x = newPositionsToCheck.x;
		max.y = newPositionsToCheck.y;
		max.z = newPositionsToCheck.z;

		isFirstTimeSet = false;
	}
}

void MeshComponent::Draw()
{
	//Plane * frustumPlanesPtr = renderer->GetFrustumPlanesPtr();

	//cout << "MIN Y: " << FCBoundingBox->min.y << endl;
	//cout << "MAX Y: " << FCBoundingBox->max.y << endl;
	//cout << endl;

	//cout << "MIN X: " << FCBoundingBox->min.x << endl;
	//cout << "MAX X: " << FCBoundingBox->max.x << endl;
	//cout << endl;

	//cout << "MIN Z: " << FCBoundingBox->min.z << endl;
	//cout << "MAX Z: " << FCBoundingBox->max.z << endl;
	//cout << endl;

	//glm::vec4 algoRaro = renderer->GetModelMatrix() * FCBoundingBox->bBoxVertices[0];
	//glm::vec4 algoRaro2 = renderer->GetModelMatrix() * FCBoundingBox->bBoxVertices[1];

	//cout << "MAX Y Moved:  " << algoRaro.y << endl;
	//cout << "MIN Y Moved:  " << algoRaro2.y << endl;
	//cout << endl;

	//cout << "MIN X Moved:  " << algoRaro.x << endl;
	//cout << "MAX X Moved:  " << algoRaro2.x << endl;
	//cout << endl;

	//cout << "MAX Z Moved:  " << algoRaro.z << endl;
	//cout << "MAX Z Moved:  " << algoRaro2.z << endl;
	//cout << endl;

	//int aux;

	//for (int i = 0; i < 6; i++)
	//{
	//	bool allBehind = true;

	//	for (int j = 0; j < 8; j++)
	//	{
	//		if (renderer->ClassifyPoint(frustumPlanesPtr[i], renderer->GetModelMatrix() * FCBoundingBox->bBoxVertices[j] /** renderer->GetModelMatrix()*/) == POSITIVE)
	//		{
	//			//cout << "CHECKEO EN MESH "  << i << "  " << frustumPlanesPtr[i].a << endl;
	//			allBehind = false;
	//			aux = j;
	//			break;
	//		}
	//	}
	//	if (allBehind)
	//	{
	//		cout << "NO SE DIBUJAAAAAAAAAAAAAAAAAAAAAAAAA: " << i << endl;
	//		cout << "EL VERTICE QUE FALLA: " << aux << endl;
	//		cout << "A: " << frustumPlanesPtr[1].a << endl;
	//		cout << "B: " << frustumPlanesPtr[1].b << endl;
	//		cout << "C: " << frustumPlanesPtr[1].c << endl;
	//		cout << "D: " << frustumPlanesPtr[1].d << endl;

	//		return;
	//	}
	//}

	meshData->Draw();
}

void MeshComponent::Update()
{

}

FrustumCullingBoundingBox::~FrustumCullingBoundingBox()
{

}

MeshComponent::~MeshComponent()
{

}