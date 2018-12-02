#include "Animation.h"



Animation::Animation(Shape * shape)
{
	receivedShape = shape;
}


Animation::~Animation()
{
	delete frameList;
}

void Animation::Update(double deltaTime)
{

}

void Animation::AddFrame(int frameRow, int frameColumn)
{
	Sprite* spriteToAdd = new Sprite(frameRow, frameColumn);

	frameList->push_back(spriteToAdd);
}
