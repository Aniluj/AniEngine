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

	//
	//g_uv_buffer_data[0] = spriteToAdd->maxU;
	//g_uv_buffer_data[1] = spriteToAdd->maxV;
	//g_uv_buffer_data[2] = spriteToAdd->minU;
	//g_uv_buffer_data[3] = spriteToAdd->maxV;
	//g_uv_buffer_data[4] = spriteToAdd->maxU;
	//g_uv_buffer_data[5] = spriteToAdd->minV;
	//g_uv_buffer_data[6] = spriteToAdd->minU;
	//g_uv_buffer_data[7] = spriteToAdd->minV;

	frameList->push_back(spriteToAdd);
}


Animation::~Animation()
{
	delete frameList;
}

void Animation::Update(double deltaTime)
{

}

void Animation::SetFirstFrameForUVBufferData()
{
	currentRow = 0;
	currentColumn = 0;


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
