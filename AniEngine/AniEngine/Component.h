#pragma once

#include "Exports.h"
#include <iostream>

using namespace std;

class ENGINEDLL_API Component
{
public:
	Component();
	~Component();

	string componentName;
	void virtual Start(const char* componentName);
	void virtual Update();
	void virtual Draw();
};

