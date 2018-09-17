#pragma once

#include "Exports.h"
#include "Renderer.h"
#include "Material.h"

class ENGINEDLL_API Entity
{
protected:
	Renderer * renderer;
public:
	Material * material;
	Entity(Renderer* rendererPtr);
	~Entity();
	void virtual Draw()=0;
};

