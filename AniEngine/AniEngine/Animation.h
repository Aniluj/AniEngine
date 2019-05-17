#pragma once

#include "Exports.h"
#include <iostream>
#include <list>
#include "Shape.h"
#include "Frame.h"
#include "glm\glm.hpp"

using namespace std;

class ENGINEDLL_API Animation
{
private:
	Shape* receivedShape;

	int currentColumn;
	int currentRow;

	int frameWidth;
	int frameHeight;
	int spritesheetWidth;
	int spritesheetHeight;

	float * g_uv_buffer_data_received;

	float speed;
	float timer;
	float elapsedTime;

public:
	Animation(
		Shape* shape,
		int & frameWidthRef,
		int & frameHeightRef,
		int & spritesheetWidth,
		int & spritesheetHeight,
		float *& g_uv_buffer_data,
		int uvBufferDataSize,
		float & animationSpeedRef,
		int & initialFrameRow,
		int & initialFrameColumn);

	~Animation();

	list<Frame*>* frameList;
	list<Frame*>::iterator frameIt;
	void Update(double & deltaTime);
	void AddFrame(int frameRow, int frameColumn);
};

