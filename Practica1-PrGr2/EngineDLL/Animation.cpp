#include "Animation.h"



Animation::Animation(Texture * textureRef,  int initialFrameID, int lastFrameID)
{
	characterTexture = textureRef;
}


Animation::~Animation()
{

}

void Animation::Update(double deltaTime)
{

}
