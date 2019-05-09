#pragma once

#include "Exports.h"
#include <iostream>

using namespace std;

class ENGINEDLL_API Window
{
private:
	void* window;
	int height;
	int width;
public:
	Window();
	~Window();
	bool Start(const int width,const int height,const char* windowName);
	bool Stop();
	void PollEvents();
	bool ShouldClose();
	void* GetWindowPtr();
	inline int GetWidth() { return width; };
	inline int GetHeight() { return height; };
};