#pragma once

#include "Exports.h"
#include "Window.h"
#include <iostream>


using namespace std;

class ENGINEDLL_API Renderer
{
private:
	Window* window;
public:
	Renderer();
	~Renderer();
	bool Start(Window* windowPtr);
	bool Stop();
	void ClearColor(float r, float g, float b, float a);
	void ClearScreen();
	void SwapBuffer();
};