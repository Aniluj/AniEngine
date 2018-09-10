#pragma once

#include "Exports.h"
#include "Renderer.h"

class ENGINEDLL_API Entity
{
protected:
	Renderer * renderer;
public:
	Entity(Renderer* rendererPtr);
	~Entity();
	void virtual Draw()=0;
};

