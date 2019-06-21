#pragma once

#include "Node.h"
#include "ShapeComponent.h"

class ENGINEDLL_API ScGraphShapeObject : public Node
{
private:
	Node * triangle;
	ShapeComponent * shapeTriangle;
	Node * rectangle;
	ShapeComponent * shapeRectangle;
public:
	ScGraphShapeObject(Renderer * rendererPtr);
	~ScGraphShapeObject();
};

