#pragma once

#include "Shape.h"
#include "BoundingBox.h"

class ENGINEDLL_API Rectangle : public Shape
{
public:
	Rectangle(Renderer * renderer);
	~Rectangle();
	BoundingBox* bbox;
	void Draw() override;
};

