#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::RegisterBoundingBox(BoundingBox* bbox)
{
	if (bbox->bboxTag == "gA")
	{
		bboxGroupA.push_back(*bbox);
	}
	else if (bbox->bboxTag == "gB")
	{
		bboxGroupB.push_back(*bbox);
	}
}

void CollisionManager::CheckForBoundingBoxCollisions()
{
	for (int i = 0; i < bboxGroupA.size; i++)
	{
		for (int j = 0; j < bboxGroupB.size; i++)
		{
			//checkear colisiones
		}
	}
}