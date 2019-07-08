#include "AnimationComponent.h"



AnimationComponent::AnimationComponent()
{
	componentType = AnimationType;
}

void AnimationComponent::Start(
							   const char * componentName,
							   Renderer * rendererPtr,
							   TextureInforForShapeComponent * texturePtr,
							   float *& g_uv_buffer_data,
							   unsigned int * uvBuffer,
							   float animationSpeed,
							   int initialFrameRow,
							   int initialFrameColumn)
{
	Component::Start(componentName);

	renderer = rendererPtr;
	frameList = new list<Frame*>();
	texture = texturePtr;
	speed = animationSpeed;
	newUVBuffer = uvBuffer;
	newUVBufferDataSize = 8;

	Frame * spriteToAdd = new Frame(initialFrameRow, initialFrameColumn);

	spriteToAdd->maxU = ((float)texture->frameWidth * (float)spriteToAdd->columPositionOfFrame) / (float)texture->spritesheetWidth;
	spriteToAdd->minU = spriteToAdd->maxU - ((float)texture->frameWidth / (float)texture->spritesheetWidth);
	spriteToAdd->minV = 1.0f - (((float)texture->frameHeight * (float)spriteToAdd->rowPositionOfFrame) / (float)texture->spritesheetHeight);
	spriteToAdd->maxV = spriteToAdd->minV + ((float)texture->frameHeight / (float)texture->spritesheetHeight);

	new_g_uv_buffer_data = new float[newUVBufferDataSize]
	{
			spriteToAdd->maxU, spriteToAdd->maxV,
			spriteToAdd->minU, spriteToAdd->maxV,
			spriteToAdd->maxU, spriteToAdd->minV,
			spriteToAdd->minU, spriteToAdd->minV
	};

	g_uv_buffer_data = new_g_uv_buffer_data;
	*newUVBuffer = renderer->GenUVBuffer(sizeof(float) * newUVBufferDataSize * 2, new_g_uv_buffer_data);

	frameList->push_back(spriteToAdd);
	frameIt = frameList->begin();
}

void AnimationComponent::AddFrame(int frameRow, int frameColumn)
{
	Frame * spriteToAdd = new Frame(frameRow, frameColumn);

	spriteToAdd->maxU = ((float)texture->frameWidth * (float)spriteToAdd->columPositionOfFrame) / (float)texture->spritesheetWidth;
	spriteToAdd->minU = spriteToAdd->maxU - ((float)texture->frameWidth / (float)texture->spritesheetWidth);
	spriteToAdd->minV = 1.0f - (((float)texture->frameHeight * (float)spriteToAdd->rowPositionOfFrame) / (float)texture->spritesheetHeight);
	spriteToAdd->maxV = spriteToAdd->minV + ((float)texture->frameHeight / (float)texture->spritesheetHeight);

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

void AnimationComponent::SetAnimationSpeed(float animationSpeed)
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