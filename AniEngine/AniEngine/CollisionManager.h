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
	list<BoundingBox*>* bboxGroupA;
	list<BoundingBox*>* bboxGroupB;
	list<BoundingCircle*>* bcircleGroupA;
	list<BoundingCircle*>* bcircleGroupB;

	list<BoundingBox*>::iterator bbIt;
	list<BoundingBox*>::iterator bbIt2;

	list<BoundingCircle*>::iterator bcIt;
	list<BoundingCircle*>::iterator bcIt2;
public:
	CollisionManager();
	~CollisionManager();
	void RegisterBoundingBox(BoundingBox* bbox);
	void RegisterBoundingCircle(BoundingCircle* bcircle);
	void CheckForBoundingBoxCollisions();
	void CheckForBoundingCircleCollisions();
};

