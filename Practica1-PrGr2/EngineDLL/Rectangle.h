#pragma once

#include "Shape.h"
#include "BoundingBox.h"
#include "BoundingCircle.h"

class ENGINEDLL_API Rectangle : public Shape
{
private:
	float mass;
public:
	Rectangle(Renderer * renderer, float massToSet);
	~Rectangle();
	BoundingBox* bbox;
	BoundingCircle* bcircle;
	void Draw() override;
};

