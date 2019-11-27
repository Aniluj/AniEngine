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

	bBoxVertices[2].x = min.x;		bBoxVertices[3].x = max.x;
	bBoxVertices[2].y = min.y;		bBoxVertices[3].y = min.y;
	bBoxVertices[2].z = min.z;		bBoxVertices[3].z = min.z;


	bBoxVertices[4].x = min.x;		bBoxVertices[5].x = max.x;
	bBoxVertices[4].y = max.y;		bBoxVertices[5].y = max.y;
	bBoxVertices[4].z = max.z;		bBoxVertices[5].z = max.z;

	bBoxVertices[6].x = min.x;		bBoxVertices[7].x = max.x;
	bBoxVertices[6].y = min.y;		bBoxVertices[7].y = min.y;
	bBoxVertices[6].z = max.z;		bBoxVertices[7].z = max.z;

	isFirstTimeSet = false;
}

void FrustumCullingBoundingBox::CompareMinsAndMax(FrustumCullingBoundingBox * FCChildBoundingBox)
{
	if (FCChildBoundingBox->bBoxVertices[0].x < bBoxVertices[0].x) // MinX
	{
		bBoxVertices[0].x = FCChildBoundingBox->bBoxVertices[0].x;
		bBoxVertices[2].x = FCChildBoundingBox->bBoxVertices[2].x;
		bBoxVertices[4].x = FCChildBoundingBox->bBoxVertices[4].x;
		bBoxVertices[6].x = FCChildBoundingBox->bBoxVertices[6].x;
	}

	if (FCChildBoundingBox->bBoxVertices[0].y > bBoxVertices[0].y) // MaxY
	{
		bBoxVertices[0].y = FCChildBoundingBox->bBoxVertices[0].y;
		bBoxVertices[1].y = FCChildBoundingBox->bBoxVertices[1].y;
		bBoxVertices[4].y = FCChildBoundingBox->bBoxVertices[4].y;
		bBoxVertices[5].y = FCChildBoundingBox->bBoxVertices[5].y;
	}

	if (FCChildBoundingBox->bBoxVertices[0].z < bBoxVertices[0].z) // MinZ
	{
		bBoxVertices[0].z = FCChildBoundingBox->bBoxVertices[0].z;
		bBoxVertices[1].z = FCChildBoundingBox->bBoxVertices[1].z;
		bBoxVertices[2].z = FCChildBoundingBox->bBoxVertices[2].z;
		bBoxVertices[3].z = FCChildBoundingBox->bBoxVertices[3].z;
	}

	if (FCChildBoundingBox->bBoxVertices[7].x > bBoxVertices[7].x) // MaxX
	{
		bBoxVertices[1].x = FCChildBoundingBox->bBoxVertices[1].x;
		bBoxVertices[3].x = FCChildBoundingBox->bBoxVertices[3].x;
		bBoxVertices[5].x = FCChildBoundingBox->bBoxVertices[5].x;
		bBoxVertices[7].x = FCChildBoundingBox->bBoxVertices[7].x;
	}

	if (FCChildBoundingBox->bBoxVertices[7].y < bBoxVertices[7].y) // MinY
	{
		bBoxVertices[2].y = FCChildBoundingBox->bBoxVertices[2].y;
		bBoxVertices[3].y = FCChildBoundingBox->bBoxVertices[3].y;
		bBoxVertices[6].y = FCChildBoundingBox->bBoxVertices[6].y;
		bBoxVertices[7].y = FCChildBoundingBox->bBoxVertices[7].y;
	}

	if (FCChildBoundingBox->bBoxVertices[7].z > bBoxVertices[7].z) // MaxZ
	{
		bBoxVertices[4].z = FCChildBoundingBox->bBoxVertices[4].z;
		bBoxVertices[5].z = FCChildBoundingBox->bBoxVertices[5].z;
		bBoxVertices[6].z = FCChildBoundingBox->bBoxVertices[6].z;
		bBoxVertices[7].z = FCChildBoundingBox->bBoxVertices[7].z;
	}
}

void FrustumCullingBoundingBox::CheckMinsAndMax(glm::vec3 newPositionsToCheck)
{
	if (isFirstTimeSet == false)
	{
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
	//glm::vec4 * frustumPlanesPtr = renderer->GetFrustumPlanesPtr();

	//if (counter <= 0)
	//{
	//	cout << endl;
	//	cout << "MIN X "<< componentName.c_str() << ": " << FCBoundingBox->min.x << endl;
	//	cout << "MAX X "<< componentName.c_str() << ": " << FCBoundingBox->max.x << endl;
	//	cout << endl;

	//	cout << "MIN Y: " << componentName.c_str() << ": " << FCBoundingBox->min.y << endl;
	//	cout << "MAX Y: " << componentName.c_str() << ": " << FCBoundingBox->max.y << endl;
	//	cout << endl;

	//	cout << "MIN Z: " << componentName.c_str() << ": " << FCBoundingBox->min.z << endl;
	//	cout << "MAX Z: " << componentName.c_str() << ": " << FCBoundingBox->max.z << endl;
	//	cout << endl;

	//	cout << "Col 1-Fil 1: " << renderer->GetModelMatrix()[0][0]; cout << "| Col 2-Fil 1: " << renderer->GetModelMatrix()[1][0]; 
	//	cout << "| Col 3-Fil 1: " << renderer->GetModelMatrix()[2][0]; cout << "| Col 4-Fil 1: " << renderer->GetModelMatrix()[3][0];
	//	cout << endl;

	//	cout << "Col 1-Fil 2: " << renderer->GetModelMatrix()[0][1]; cout << "| Col 2-Fil 2: " << renderer->GetModelMatrix()[1][1];
	//	cout << "| Col 3-Fil 2: " << renderer->GetModelMatrix()[2][1]; cout << "| Col 4-Fil 2: " << renderer->GetModelMatrix()[3][1];
	//	cout << endl;

	//	cout << "Col 1-Fil 3: " << renderer->GetModelMatrix()[0][2]; cout << "| Col 2-Fil 3: " << renderer->GetModelMatrix()[1][2];
	//	cout << "| Col 3-Fil 3: " << renderer->GetModelMatrix()[2][2]; cout << "| Col 4-Fil 3: " << renderer->GetModelMatrix()[3][2];
	//	cout << endl;

	//	cout << "Col 1-Fil 4: " << renderer->GetModelMatrix()[0][3]; cout << "| Col 2-Fil 4: " << renderer->GetModelMatrix()[1][3];
	//	cout << "| Col 3-Fil 4: " << renderer->GetModelMatrix()[2][3]; cout << "| Col 4-Fil 4: " << renderer->GetModelMatrix()[3][3];
	//	cout << endl;
	//}

	//counter++;

	//for (int i = 0; i < 6; i++)
	//{
	//	bool allBehind = true;

	//	for (int j = 0; j < 8; j++)
	//	{
	//		if (renderer->ClassifyPoint(frustumPlanesPtr[i], renderer->GetModelMatrix() * FCBoundingBox->bBoxVertices[j]) == POSITIVE)
	//		{
	//			allBehind = false;
	//			break;
	//		}
	//	}
	//	if (allBehind)
	//	{
	//		cout << "NO SE DIBUJA: " << componentName.c_str() << "||  con Plano: " << i <<endl;
	//		//cout << "A: " << frustumPlanesPtr[1].a << endl;
	//		//cout << "B: " << frustumPlanesPtr[1].b << endl;
	//		//cout << "C: " << frustumPlanesPtr[1].c << endl;
	//		//cout << "D: " << frustumPlanesPtr[1].d << endl;

	//		return;
	//	}
	//}

	//cout << "SE DIBUJA: " << componentName.c_str() << endl;
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