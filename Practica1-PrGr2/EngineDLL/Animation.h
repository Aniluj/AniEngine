#pragma once

#include "Exports.h"
#include <iostream>
#include "Texture.h"
#include "glm\glm.hpp"

class ENGINEDLL_API Animation
{
private:
	Texture * characterTexture;
public:
	Animation(Texture * textureRef, int initialFrameID, int lastFrameID);
	~Animation();
	void Update(double deltaTime);
};

