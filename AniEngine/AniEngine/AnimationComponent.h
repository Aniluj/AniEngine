#pragma once
#include "Component.h"
#include "Renderer.h"
#include "Frame.h"
#include "Timer.h"
#include <list>

using namespace std;

class ENGINEDLL_API AnimationComponent : public Component
{
private:
	int currentColumn;
	int currentRow;

	int frameWidth;
	int frameHeight;
	int spritesheetWidth;
	int spritesheetHeight;

	float * new_g_uv_buffer_data;
	unsigned int * newUVBuffer;
	int newUVBufferDataSize;

	float speed;
	float timer;

	list<Frame*>* frameList;
	list<Frame*>::iterator frameIt;
	Renderer * renderer;
public:
	AnimationComponent();

	void Start(
			   const char * componentName,
			   Renderer * rendererPtr,
			   int & frameWidthRef,
			   int & frameHeightRef,
			   int & spritesheetWidthRef,
			   int & spritesheetHeightRef,
			   float *& g_uv_buffer_data,
			   unsigned int * uvBufferReceived,
			   float & animationSpeedRef,
			   int & initialFrameRow,
			   int & initialFrameColumn);
	void AddFrame(int frameRow, int frameColumn);
	void Update() override;
	void SetAnimationSpeed(int animationSpeed);
	void Draw() override;

	~AnimationComponent();
};

