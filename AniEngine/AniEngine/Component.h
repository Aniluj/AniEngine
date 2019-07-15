#pragma once

#include "Exports.h"
#include <iostream>

using namespace std;

enum ComponentType
{
	DefaultType,
	TransformType,
	MeshLoaderType,
	MeshType,
	ShapeType,
	AnimationType
};

class ENGINEDLL_API Component
{
public:
	Component();
	~Component();

	string componentName;
	ComponentType componentType;
	void virtual Start(const char* componentName);
	void virtual Update();
	void virtual Draw();
};

