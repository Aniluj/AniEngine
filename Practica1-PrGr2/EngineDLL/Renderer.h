#pragma once

#include "Exports.h"
#include "Window.h"
#include <iostream>


using namespace std;

class ENGINEDLL_API Renderer
{
public:
	Renderer();
	~Renderer();
	bool Start(Window* window);
	bool Stop();
	void ClearColor(float r, float g, float b);
	void ClearScreen();
	void SwapBuffer();
};