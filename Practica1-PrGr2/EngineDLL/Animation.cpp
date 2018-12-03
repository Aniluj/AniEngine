#include "Animation.h"



Animation::Animation(
	Shape * shape,
	int & frameWidthRef,
	int & frameHeightRef,
	int & spritesheetWidthRef,
	int & spritesheetHeightRef,
	float *& g_uv_buffer_data,
	int uvBufferDataSize,
	float & animationSpeedRef,
	int & initialFrameRow,
	int & initialFrameColumn)
{
	frameList = new list<Sprite*>();
	receivedShape = shape;
	frameWidth = frameWidthRef;
	frameHeight = frameHeightRef;
	spritesheetWidth = spritesheetWidthRef;
	spritesheetHeight = spritesheetHeightRef;
	speed = animationSpeedRef;

	Sprite * spriteToAdd = new Sprite(initialFrameRow, initialFrameColumn);

	spriteToAdd->maxU = ((float)frameWidth * (float)spriteToAdd->columPositionOfFrame) / (float)spritesheetWidth;
	spriteToAdd->minU = spriteToAdd->maxU - ((float)frameWidth / (float)spritesheetWidth);
	spriteToAdd->minV = 1.0f - (((float)frameHeight * (float)spriteToAdd->rowPositionOfFrame) / (float)spritesheetHeight);
	spriteToAdd->maxV = spriteToAdd->minV + ((float)frameHeight / (float)spritesheetHeight);

	g_uv_buffer_data_received = new float[uvBufferDataSize]
	{
		spriteToAdd->maxU, spriteToAdd->maxV,
		spriteToAdd->minU, spriteToAdd->maxV,
		spriteToAdd->maxU, spriteToAdd->minV,
		spriteToAdd->minU, spriteToAdd->minV
	};
	
	g_uv_buffer_data = g_uv_buffer_data_received;

	frameList->push_back(spriteToAdd);
	frameIt = frameList->begin();
}


Animation::~Animation()
{
	delete frameList;
}

void Animation::Update(double & deltaTime)
{
	timer += deltaTime;

	cout << "COUNT: " << timer << endl;

	if (timer >= speed)
	{
		if (frameIt != frameList->end())
		{
			g_uv_buffer_data_received[0] = (*frameIt)->maxU;	g_uv_buffer_data_received[1] = (*frameIt)->maxV;
			g_uv_buffer_data_received[2] = (*frameIt)->minU;	g_uv_buffer_data_received[3] = (*frameIt)->maxV;
			g_uv_buffer_data_received[4] = (*frameIt)->maxU;	g_uv_buffer_data_received[5] = (*frameIt)->minV;
			g_uv_buffer_data_received[6] = (*frameIt)->minU;	g_uv_buffer_data_received[7] = (*frameIt)->minV;

			frameIt++;
		}
		else
		{
			frameIt = frameList->begin();
		}
		
		timer = 0;
	}
}

void Animation::AddFrame(int frameRow, int frameColumn)
{
	Sprite* spriteToAdd = new Sprite(frameRow, frameColumn);

	spriteToAdd->maxU = ((float)frameWidth * (float)spriteToAdd->columPositionOfFrame) / (float)spritesheetWidth;
	spriteToAdd->minU = spriteToAdd->maxU - ((float)frameWidth / (float)spritesheetWidth);
	spriteToAdd->minV = 1.0f - (((float)frameHeight * (float)spriteToAdd->rowPositionOfFrame) / (float)spritesheetHeight);
	spriteToAdd->maxV = spriteToAdd->minV + ((float)frameHeight / (float)spritesheetHeight);

	frameList->push_back(spriteToAdd);
}
