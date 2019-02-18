#pragma once

#include "Exports.h"
#include "Shape.h"

enum TileType
{
	WallOfBricks,
	Background
};

struct TileInfo
{
	TileType typeOfTheTile;
	float* tileUVData;
};

class ENGINEDLL_API Tilemap : public Shape
{
public:
	Tilemap(Renderer * rendererPtr);
	~Tilemap();
};

