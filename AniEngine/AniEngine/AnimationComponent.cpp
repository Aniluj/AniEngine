#include "AnimationComponent.h"



AnimationComponent::AnimationComponent()
{
	componentType = AnimationType;
}

void AnimationComponent::Start(
							   const char * componentName,
							   Renderer * rendererPtr,
							   int & frameWidthRef,
							   int & frameHeightRef,
							   int & spritesheetWidthRef,
							   int & spritesheetHeightRef,
							   float *& g_uv_buffer_data,
							   unsigned int * uvBuffer,
							   float & animationSpeedRef,
							   int & initialFrameRow,
							   int & initialFrameColumn)
{
	Component::Start(componentName);

	renderer = rendererPtr;
	frameList = new list<Frame*>();
	frameWidth = frameWidthRef;
	frameHeight = frameHeightRef;
	spritesheetWidth = spritesheetWidthRef;
	spritesheetHeight = spritesheetHeightRef;
	speed = animationSpeedRef;
	newUVBuffer = uvBuffer;
	newUVBufferDataSize = 8;

	Frame * spriteToAdd = new Frame(initialFrameRow, initialFrameColumn);

	spriteToAdd->maxU = ((float)frameWidth * (float)spriteToAdd->columPositionOfFrame) / (float)spritesheetWidth;
	spriteToAdd->minU = spriteToAdd->maxU - ((float)frameWidth / (float)spritesheetWidth);
	spriteToAdd->minV = 1.0f - (((float)frameHeight * (float)spriteToAdd->rowPositionOfFrame) / (float)spritesheetHeight);
	spriteToAdd->maxV = spriteToAdd->minV + ((float)frameHeight / (float)spritesheetHeight);

	new_g_uv_buffer_data = new float[newUVBufferDataSize]
	{
			spriteToAdd->maxU, spriteToAdd->maxV,
			spriteToAdd->minU, spriteToAdd->maxV,
			spriteToAdd->maxU, spriteToAdd->minV,
			spriteToAdd->minU, spriteToAdd->minV
	};

	g_uv_buffer_data = new_g_uv_buffer_data;

	frameList->push_back(spriteToAdd);
	frameIt = frameList->begin();
}

void AnimationComponent::AddFrame(int frameRow, int frameColumn)
{
	Frame* spriteToAdd = new Frame(frameRow, frameColumn);

	spriteToAdd->maxU = ((float)frameWidth * (float)spriteToAdd->columPositionOfFrame) / (float)spritesheetWidth;
	spriteToAdd->minU = spriteToAdd->maxU - ((float)frameWidth / (float)spritesheetWidth);
	spriteToAdd->minV = 1.0f - (((float)frameHeight * (float)spriteToAdd->rowPositionOfFrame) / (float)spritesheetHeight);
	spriteToAdd->maxV = spriteToAdd->minV + ((float)frameHeight / (float)spritesheetHeight);

	frameList->push_back(spriteToAdd);
}

void AnimationComponent::Update()
{
	timer += Timer::GetDeltaTime();

	if (timer >= speed)
	{
		if (frameIt != frameList->end())
		{
			new_g_uv_buffer_data[0] = (*frameIt)->maxU;	new_g_uv_buffer_data[1] = (*frameIt)->maxV;
			new_g_uv_buffer_data[2] = (*frameIt)->minU;	new_g_uv_buffer_data[3] = (*frameIt)->maxV;
			new_g_uv_buffer_data[4] = (*frameIt)->maxU;	new_g_uv_buffer_data[5] = (*frameIt)->minV;
			new_g_uv_buffer_data[6] = (*frameIt)->minU;	new_g_uv_buffer_data[7] = (*frameIt)->minV;

			frameIt++;
		}
		else
		{
			frameIt = frameList->begin();
		}

		*newUVBuffer = renderer->GenUVBuffer(sizeof(float) * newUVBufferDataSize * 2, new_g_uv_buffer_data);
		timer = 0;
	}
}

void AnimationComponent::SetAnimationSpeed(int animationSpeed)
{
	speed = animationSpeed;
}

void AnimationComponent::Draw()
{
	Component::Draw();
}

AnimationComponent::~AnimationComponent()
{
	delete frameList;
}