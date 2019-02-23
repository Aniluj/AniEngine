#pragma once

#include "Exports.h"
#include "Shape.h"
#include "BMPLoader.h"
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

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
private:
	vector<vector<TileInfo>> tiles;
	vector<vector<int>> tilemap;

	const char* tilesetPath;
	unsigned int texture;

	unsigned int tileWidth;
	unsigned int tileHeight;
	int tilesetWidth;
	int tilesetHeight;
	const unsigned int tilesetRows;
	const unsigned int tilesetColumns;
	const unsigned int tilemapWidth;
	const unsigned int tilemapHeight;
	unsigned int tilemapRows;
	unsigned int tilemapColumns;
public:
	Tilemap(
		Renderer * renderer,
		/*Material* material,*/						
		const unsigned int tsColumns,	
		const unsigned int tsRows,	
		const unsigned int tmWidth,
		const unsigned int tmHeight,
		const char* tsPath,
		const char* tilemapPath
			);
	vector<vector<int>> LoadTilemap(const char* tilemapPath);
	void Draw() override;
	~Tilemap();
};

