#pragma once

#include "Node.h"
#include "ShapeComponent.h"
#include "AnimationComponent.h"

class ENGINEDLL_API ScGraphShapeObject : public Node
{
private:
	Node * triangle;
	ShapeComponent * triangleShape;
	Node * sprite;
	ShapeComponent * spriteShape;
	AnimationComponent * spriteAnimation;
public:
	ScGraphShapeObject(Renderer * rendererPtr);
	~ScGraphShapeObject();
};

