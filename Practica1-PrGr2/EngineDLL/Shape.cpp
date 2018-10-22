#include "Shape.h"



Shape::Shape(Renderer* rendererPtr):Entity(rendererPtr)
{
}


Shape::~Shape()
{
	delete material;
}
