#pragma once

#include "Exports.h"
#include "Renderer.h"

class ENGINEDLL_API Entity
{
public:
	Entity();
	~Entity();
	void virtual Draw();
};

