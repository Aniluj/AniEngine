#include "Tilemap.h"


Tilemap::Tilemap(
	Renderer * renderer,
	/*Material* material,*/
	const unsigned int tsColumns,
	const unsigned int tsRows,
	const unsigned int tmWidth,
	const unsigned int tmHeight,
	const char* tsPath,
	const char* tilemapPath
				) : Shape(renderer), tilesetColumns(tsColumns), tilesetRows(tsRows), tilemapWidth(tmWidth), tilemapHeight(tmHeight), tilesetPath(tsPath)
{
	texture = BMPLoader::LoadBMP(tilesetPath, tilesetWidth, tilesetHeight);

	tileWidth = tilesetWidth / tilesetColumns;
	tileHeight = tilesetHeight / tilesetRows;

	tilemapColumns = (int)(tilemapWidth / tileWidth);
	tilemapRows = (int)(tilemapHeight / tileHeight);

	tilemap = LoadTilemap(tilemapPath);
}

vector<vector<int>> Tilemap::LoadTilemap(const char* tilemapPath)
{
	ifstream tilemapFile;

	vector<std::vector<int>> tilemap;

	string line;
	string value;

	tilemapFile.open(tilemapPath, std::ios::in);

	if (!tilemapFile.good())
	{
		throw std::ios::failure("The level file could not be opened.");
	}

	while (getline(tilemapFile, line))
	{
		vector<int> v;              
		stringstream s(line);       
		while (getline(s, value, ','))
		{
			v.push_back(stoi(value)); 
		}
		tilemap.push_back(v);       
	}

	for (auto& row : tilemap)
	{               
		for (auto& value : row)   
		{ 
			cout << value << "  ";
		}
		cout << "\n";                  
	}

	return tilemap;
}

void Tilemap::Draw()
{

}

Tilemap::~Tilemap()
{
}
