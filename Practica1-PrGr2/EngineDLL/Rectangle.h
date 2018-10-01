#pragma once
#include "Shape.h"
class ENGINEDLL_API Rectangle : public Shape
{
public:
	Rectangle(Renderer * renderer);
	~Rectangle();
	void Draw() override;
};

