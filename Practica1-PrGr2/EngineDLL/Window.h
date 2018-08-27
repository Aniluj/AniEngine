#pragma once

#include "Exports.h"
#include <iostream>

using namespace std;

class ENGINEDLL_API Window
{
private:
	void* window;
public:
	Window();
	~Window();
	bool Start(const int width,const int height,const char* windowName);
	bool Stop();
	void PollEvents();
	bool ShouldClose();
};

