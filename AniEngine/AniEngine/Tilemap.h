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
	Background,
	Wall
};

struct TileInfo
{
	static const int VERTEX_AMOUNT = 4;
	static const int VERTEX_COMPONENTS = 3;

	static unsigned int tileWidth;
	static unsigned int tileHeight;

	TileType tileType;
	float* tileUVData;
};

class ENGINEDLL_API Tilemap : public Shape
{
private:
	TileInfo** tiles;
	TileInfo** onScreenTiles;
	int** tilemap;

	const char* tilesetPath;
	unsigned int texture;

	const unsigned int tilemapWidth;
	const unsigned int tilemapHeight;

	//unsigned int tilesRows;
	//unsigned int tilesColumns;

	const unsigned int tilesetRows;
	const unsigned int tilesetColumns;

	unsigned int screenTilesRows;
	unsigned int screenTilesColumns;

	unsigned int levelRows;
	unsigned int levelColumns;

	float lastRowOffset;
	float lastColumnOffset;

	int tilesetWidth;
	int tilesetHeight;

	glm::vec2 accumTrans;

	int** LoadTilemap(const char* tilemapPath);
	TileInfo** LoadTiles();

	TileInfo** CreateOnScreenTiles();

	float* SetScreenTilesVertices(int totalTiles) const;
	float* CreateUvBuffer() const;
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

	void SetTileProperty(unsigned int tyleIndex, TileType tileType);

	void UpdateVerticesUV();

	void ScrollView(float x, float y);

	TileInfo GetTile(unsigned int tileIndex) const;
	TileType GetTileType(unsigned int row, unsigned int column) const;

	glm::vec2 WorldToGrid(float posX, float posY) const;
	glm::vec2 GridToWorld(unsigned int row, unsigned int col) const;

	float getLastRowOffset() const { return lastRowOffset; }
	float getLastColumnOffset() const { return lastColumnOffset; }

	void Draw() override;
	~Tilemap();
};

