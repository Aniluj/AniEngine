#pragma once
#include "Component.h"
#include "ShapeComponent.h"
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

	TextureInforForShapeComponent * texture;

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
			   TextureInforForShapeComponent * texturePtr,
			   float *& g_uv_buffer_data,
			   unsigned int * uvBufferReceived,
			   float animationSpeed,
			   int initialFrameRow,
			   int initialFrameColumn);
	void AddFrame(int frameRow, int frameColumn);
	void Update() override;
	void SetAnimationSpeed(float animationSpeed);
	void Draw() override;

	~AnimationComponent();
};

