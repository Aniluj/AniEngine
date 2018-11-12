#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
	bboxGroupA = new list<BoundingBox*>();
	bboxGroupB = new list<BoundingBox*>();
	bcircleGroupA = new list<BoundingCircle*>();
	bcircleGroupB = new list<BoundingCircle*>();
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
		bboxGroupA->push_back(bbox);
	}
	else if (bbox->bboxTag == "gB")
	{
		bboxGroupB->push_back(bbox);
	}
}

void CollisionManager::RegisterBoundingCircle(BoundingCircle* bcircle)
{
	if (bcircle->bcircleTag == "gA")
	{
		bcircleGroupA->push_back(bcircle);
	}
	else if(bcircle->bcircleTag == "gB")
	{
		bcircleGroupB->push_back(bcircle);
	}
}

void CollisionManager::CheckForBoundingBoxCollisions()
{

	for (bbIt = bboxGroupA->begin(); bbIt != bboxGroupA->end(); bbIt++)
	{
		for (bbIt2 = bboxGroupB->begin(); bbIt2 != bboxGroupB->end(); bbIt2++)
		{
			glm::vec3 diff = (*bbIt2)->vectorPosition - (*bbIt)->vectorPosition;

			float deltX = glm::abs(diff.x);
			float deltY = glm::abs(diff.y);
			cout << deltX << endl;
			cout << deltY << endl;
			float sumAndDivOfHeight = ((*bbIt)->height / 2) + ((*bbIt2)->height / 2);
			float sumAndDivOfWidth = ((*bbIt)->width / 2) + ((*bbIt2)->width / 2);
			cout << sumAndDivOfHeight << endl;
			cout << sumAndDivOfWidth << endl;
			if (deltX <= sumAndDivOfWidth && deltY <= sumAndDivOfHeight)
			{
				//cout << "BOX COLLISION" << endl;
				float penetrationInX = sumAndDivOfWidth - deltX;
				float penetrationInY = sumAndDivOfHeight - deltY;

				if (penetrationInX > penetrationInY)
				{
					cout << "P en Y" << endl;

					float percentageOfExpulsionOb1 = (*bbIt)->mass / ((*bbIt)->mass + (*bbIt2)->mass);
					float percentageOfExpulsionOb2 = (*bbIt2)->mass / ((*bbIt)->mass + (*bbIt2)->mass);

					if ((*bbIt)->vectorPosition.y  > (*bbIt2)->vectorPosition.y)
					{
						cout << "El objeto ingresó por debajo" << endl;

						cout << percentageOfExpulsionOb1 << endl;
						cout << percentageOfExpulsionOb2 << endl;

						(*bbIt)->receivedShape->Translate((*bbIt)->vectorPosition.x, (*bbIt)->vectorPosition.y + (percentageOfExpulsionOb1 * penetrationInY), (*bbIt)->vectorPosition.z);
						(*bbIt2)->receivedShape->Translate((*bbIt2)->vectorPosition.x, (*bbIt2)->vectorPosition.y - (percentageOfExpulsionOb2 * penetrationInY), (*bbIt2)->vectorPosition.z);
					}
				}
				else if (penetrationInY > penetrationInX)
				{
					cout << "P en X" << endl;

					float percentageOfExpulsionOb1 = (*bbIt)->mass / ((*bbIt)->mass + (*bbIt2)->mass);
					float percentageOfExpulsionOb2 = (*bbIt2)->mass / ((*bbIt)->mass + (*bbIt2)->mass);

					if ((*bbIt)->vectorPosition.x > (*bbIt2)->vectorPosition.x)
					{
						(*bbIt)->receivedShape->Translate((*bbIt)->vectorPosition.x + (percentageOfExpulsionOb1 * penetrationInX), (*bbIt)->vectorPosition.y, (*bbIt)->vectorPosition.z);
						(*bbIt2)->receivedShape->Translate((*bbIt2)->vectorPosition.x - (percentageOfExpulsionOb2 * penetrationInX), (*bbIt2)->vectorPosition.y, (*bbIt2)->vectorPosition.z);
					}
				}
			}
		}
	}
}

void CollisionManager::CheckForBoundingCircleCollisions()
{
	for(bcIt = bcircleGroupA->begin(); bcIt != bcircleGroupA->end(); bcIt++)
	{
		for(bcIt2 = bcircleGroupB->begin(); bcIt2!=bcircleGroupB->end(); bcIt2++)
		{
			glm::vec3 diff = (*bcIt2)->vectorPosition - (*bcIt)->vectorPosition;

			float deltX = glm::abs(diff.x);
			float deltY = glm::abs(diff.y);
			cout << deltX << endl;
			cout << deltY << endl;
			float distSqr = ((deltX * deltX) + (deltY*deltY));
			float sumAndSquaredRadius = (((*bcIt)->radius + (*bcIt2)->radius) * ((*bcIt)->radius + (*bcIt2)->radius));

			if (distSqr <= sumAndSquaredRadius)
			{
				cout << "CIRCLE COLLISION" << endl;

				float dist = glm::sqrt(distSqr);
				float penetration = ((*bcIt)->radius + (*bcIt2)->radius) - dist;
				glm::vec3 dir = glm::normalize(diff);
			}
		}
	}
}