#pragma once

#include "Exports.h"
#include <iostream>
#include "glm\glm.hpp"
#include "BoundingBox.h"
#include "BoundingCircle.h"
#include <list>

using namespace std;

class ENGINEDLL_API CollisionManager
{
private:
	list<BoundingBox> bboxGroupA;
	list<BoundingBox> bboxGroupB;
	list<BoundingCircle> bcircleGroupA;
	list<BoundingCircle> bcircleGroupB;
public:
	CollisionManager();
	~CollisionManager();
	void RegisterBoundingBox(BoundingBox bbox);
	void RegisterBoundingCircle(BoundingCircle bcircle);
	void CheckForBoundingBoxCollisions(BoundingBox bbox);
	void CheckForBoundingCircleCollisions(BoundingCircle bcircle);
};

