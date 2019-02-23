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
			glm::vec3 diff = (*bbIt2)->receivedShape->vectorPosition - (*bbIt)->receivedShape->vectorPosition;

			float deltX = glm::abs(diff.x);
			float deltY = glm::abs(diff.y);
			//cout << "Deltx " << deltX << endl;
			//cout << "DeltY " << deltY << endl;
			float minimumDistInY = (((*bbIt)->height + (*bbIt2)->height)/2);
			float minimumDistInX = (((*bbIt)->width +(*bbIt2)->width)/2);
			//cout << "MinimunDistY " << minimumDistInY << endl;
			//cout << "MinimunDistX" << minimumDistInX << endl;
			if (deltX < minimumDistInX && deltY < minimumDistInY)
			{
				//cout << "BOX COLLISION" << endl;
				float penetrationInX = minimumDistInX - deltX;
				float penetrationInY = minimumDistInY - deltY;

				float percentageOfExpulsionOb1 = (*bbIt)->mass / ((*bbIt)->mass + (*bbIt2)->mass);
				float percentageOfExpulsionOb2 = (*bbIt2)->mass / ((*bbIt)->mass + (*bbIt2)->mass);

				if (penetrationInX > penetrationInY)
				{
					//cout << "P en Vertical" << endl;

					if ((*bbIt)->receivedShape->vectorPosition.y  > (*bbIt2)->receivedShape->vectorPosition.y)
					{
						if ((*bbIt)->isStatic || (*bbIt2)->isStatic)
						{
							if ((*bbIt)->isStatic)
							{
								(*bbIt2)->receivedShape->Translate((*bbIt2)->receivedShape->vectorPosition.x, (*bbIt2)->receivedShape->vectorPosition.y - ((percentageOfExpulsionOb1 + percentageOfExpulsionOb2) * penetrationInY), (*bbIt2)->receivedShape->vectorPosition.z);
							}
							else if ((*bbIt2)->isStatic)
							{
								(*bbIt)->receivedShape->Translate((*bbIt)->receivedShape->vectorPosition.x, (*bbIt)->receivedShape->vectorPosition.y + ((percentageOfExpulsionOb1 + percentageOfExpulsionOb2) * penetrationInY), (*bbIt)->receivedShape->vectorPosition.z);
							}
						}
						else
						{
							(*bbIt)->receivedShape->Translate((*bbIt)->receivedShape->vectorPosition.x, (*bbIt)->receivedShape->vectorPosition.y + (percentageOfExpulsionOb2 * penetrationInY), (*bbIt)->receivedShape->vectorPosition.z);
							(*bbIt2)->receivedShape->Translate((*bbIt2)->receivedShape->vectorPosition.x, (*bbIt2)->receivedShape->vectorPosition.y - (percentageOfExpulsionOb1 * penetrationInY), (*bbIt2)->receivedShape->vectorPosition.z);
						}
					}
					else if ((*bbIt2)->receivedShape->vectorPosition.y >= (*bbIt)->receivedShape->vectorPosition.y)
					{
						if ((*bbIt)->isStatic || (*bbIt2)->isStatic)
						{
							if ((*bbIt)->isStatic)
							{
								(*bbIt2)->receivedShape->Translate((*bbIt2)->receivedShape->vectorPosition.x, (*bbIt2)->receivedShape->vectorPosition.y + ((percentageOfExpulsionOb1 + percentageOfExpulsionOb2) * penetrationInY), (*bbIt2)->receivedShape->vectorPosition.z);
							}
							else if ((*bbIt2)->isStatic)
							{
								(*bbIt)->receivedShape->Translate((*bbIt)->receivedShape->vectorPosition.x, (*bbIt)->receivedShape->vectorPosition.y - ((percentageOfExpulsionOb1 + percentageOfExpulsionOb2) * penetrationInY), (*bbIt)->receivedShape->vectorPosition.z);
							}
						}
						else
						{
							(*bbIt)->receivedShape->Translate((*bbIt)->receivedShape->vectorPosition.x, (*bbIt)->receivedShape->vectorPosition.y - (percentageOfExpulsionOb2 * penetrationInY), (*bbIt)->receivedShape->vectorPosition.z);
							(*bbIt2)->receivedShape->Translate((*bbIt2)->receivedShape->vectorPosition.x, (*bbIt2)->receivedShape->vectorPosition.y + (percentageOfExpulsionOb1 * penetrationInY), (*bbIt2)->receivedShape->vectorPosition.z);

						}
					}
				}
				else if (penetrationInY > penetrationInX)
				{
					//cout << "P en Horizontal" << endl;


					//cout << "PercentExp1 " << percentageOfExpulsionOb1 << endl;
					//cout << "PercentExp2 " << percentageOfExpulsionOb2 << endl;
					//cout << "PenY" << penetrationInY;


					if ((*bbIt)->receivedShape->vectorPosition.x >= (*bbIt2)->receivedShape->vectorPosition.x)
					{
						//cout << "Obj1*Pen " << percentageOfExpulsionOb1 * penetrationInX << endl;
						//cout << "Obj2*Pen " << percentageOfExpulsionOb2 * penetrationInX << endl;

						if ((*bbIt)->isStatic || (*bbIt2)->isStatic)
						{
							if ((*bbIt)->isStatic)
							{
								(*bbIt2)->receivedShape->Translate((*bbIt2)->receivedShape->vectorPosition.x - ((percentageOfExpulsionOb1 + percentageOfExpulsionOb2) * penetrationInX), (*bbIt2)->receivedShape->vectorPosition.y, (*bbIt2)->receivedShape->vectorPosition.z);
							}
							else if ((*bbIt2)->isStatic)
							{
								(*bbIt)->receivedShape->Translate((*bbIt)->receivedShape->vectorPosition.x + ((percentageOfExpulsionOb1 + percentageOfExpulsionOb2) * penetrationInX), (*bbIt)->receivedShape->vectorPosition.y, (*bbIt)->receivedShape->vectorPosition.z);
							}
						}
						else
						{
							(*bbIt)->receivedShape->Translate((*bbIt)->receivedShape->vectorPosition.x + (percentageOfExpulsionOb2 * penetrationInX), (*bbIt)->receivedShape->vectorPosition.y, (*bbIt)->receivedShape->vectorPosition.z);
							(*bbIt2)->receivedShape->Translate((*bbIt2)->receivedShape->vectorPosition.x - (percentageOfExpulsionOb1 * penetrationInX), (*bbIt2)->receivedShape->vectorPosition.y, (*bbIt2)->receivedShape->vectorPosition.z);

						}
					}
					else if ((*bbIt2)->receivedShape->vectorPosition.x > (*bbIt)->receivedShape->vectorPosition.x)
					{
						//cout << "Obj1*Pen " << percentageOfExpulsionOb1 * penetrationInX << endl;
						//cout << "Obj2*Pen " << percentageOfExpulsionOb2 * penetrationInX << endl;

						if ((*bbIt)->isStatic || (*bbIt2)->isStatic)
						{
							if ((*bbIt)->isStatic)
							{
								(*bbIt2)->receivedShape->Translate((*bbIt2)->receivedShape->vectorPosition.x + ((percentageOfExpulsionOb1 + percentageOfExpulsionOb2) * penetrationInX), (*bbIt2)->receivedShape->vectorPosition.y, (*bbIt2)->receivedShape->vectorPosition.z);
							}
							else if ((*bbIt2)->isStatic)
							{
								(*bbIt)->receivedShape->Translate((*bbIt)->receivedShape->vectorPosition.x - ((percentageOfExpulsionOb1 + percentageOfExpulsionOb2) * penetrationInX), (*bbIt)->receivedShape->vectorPosition.y, (*bbIt)->receivedShape->vectorPosition.z);
							}
						}
						else
						{
							(*bbIt)->receivedShape->Translate((*bbIt)->receivedShape->vectorPosition.x - (percentageOfExpulsionOb2 * penetrationInX), (*bbIt)->receivedShape->vectorPosition.y, (*bbIt)->receivedShape->vectorPosition.z);
							(*bbIt2)->receivedShape->Translate((*bbIt2)->receivedShape->vectorPosition.x + (percentageOfExpulsionOb1 * penetrationInX), (*bbIt2)->receivedShape->vectorPosition.y, (*bbIt2)->receivedShape->vectorPosition.z);
						}
					}
				}
			}
		}
	}
}

/*void CollisionManager::CheckForBoundingCircleCollisions()
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
}*/