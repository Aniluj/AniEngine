#include "BoundingCircle.h"



BoundingCircle::BoundingCircle(const char * tag)
{
	bcircleTag = tag;

	vectorPosition = glm::vec3(0.0f);
}


BoundingCircle::~BoundingCircle()
{
}

void BoundingCircle::UpdateBoundingCircleModel(float radiusParam, glm::vec3 entityVectorPosition, float &massToSet)
{
	vectorPosition = entityVectorPosition;
	radius = radiusParam;
	mass = massToSet;
}
