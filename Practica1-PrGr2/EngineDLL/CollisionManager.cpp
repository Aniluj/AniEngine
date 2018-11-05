#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
	bboxGroupA = new list<BoundingBox>();
	bboxGroupB = new list<BoundingBox>();
	bcircleGroupA = new list<BoundingCircle>();
	bcircleGroupB = new list<BoundingCircle>();
}

CollisionManager::~CollisionManager()
{
	delete bboxGroupA;
	delete bboxGroupB;
	delete bcircleGroupA;
	delete bcircleGroupB;
}

void CollisionManager::RegisterBoundingBox(BoundingBox* bbox)
{
	if (bbox->bboxTag == "gA")
	{
		bboxGroupA->push_back(*bbox);
	}
	else if (bbox->bboxTag == "gB")
	{
		bboxGroupB->push_back(*bbox);
	}
}

void CollisionManager::CheckForBoundingBoxCollisions()
{
	for (list<BoundingBox>::iterator it = bboxGroupA->begin; it != bboxGroupA->end; it++)
	{
		for (list<BoundingBox>::iterator it2 = bboxGroupB->begin; it2 != bboxGroupB->end; it2++)
		{
			
		}
	}
}