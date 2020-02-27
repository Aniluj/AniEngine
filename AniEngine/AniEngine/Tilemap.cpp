#include "Tilemap.h"


unsigned int TileInfo::tileWidth = 0;
unsigned int TileInfo::tileHeight = 0;

Tilemap::Tilemap(
	Renderer * renderer,
	/*Material* material,*/
	const unsigned int tilesetColumns,
	const unsigned int tilesetRows,
	const unsigned int tilemapWidth,
	const unsigned int tilemapHeight,
	const char* tilesetPath,
	const char* tilemapPath
				) :
	Shape(renderer),
	tilesetColumns(tilesetColumns),
	tilesetRows(tilesetRows),
	tilemapWidth(tilemapWidth),
	tilemapHeight(tilemapHeight),
	tilesetPath(tilesetPath),
	accumTrans(glm::vec2(0.0f, 0.0f))
{
	texture = BMPLoader::LoadBMP(tilesetPath, tilesetWidth, tilesetHeight, true);

	TileInfo::tileWidth = tilesetWidth / tilesetColumns;
	TileInfo::tileHeight = tilesetHeight / tilesetRows;

	int windowWidth = renderer->GetRenderWindow()->GetWidth();
	int windowHeight = renderer->GetRenderWindow()->GetHeight();

	lastRowOffset = windowHeight % TileInfo::tileHeight;
	lastColumnOffset = windowWidth % TileInfo::tileWidth;

	screenTilesRows = (int)(windowHeight / TileInfo::tileHeight + 1);
	screenTilesColumns = (int)(windowWidth / TileInfo::tileWidth + 1);

	tiles = LoadTiles();
	tilemap = LoadTilemap(tilemapPath);
	g_uv_buffer_data = CreateUvBuffer();
	onScreenTiles = CreateOnScreenTiles();

	UpdateVerticesUV();
}

TileInfo** Tilemap::LoadTiles()
{
	TileInfo** tiles = new TileInfo*[tilesetRows];

	for (int i = 0; i < tilesetRows; i++)
	{
		tiles[i] = new TileInfo[tilesetColumns];
	}

	for (int y = 0; y < tilesetRows; y++)
	{
		for (int x = 0; x < tilesetColumns; x++)
		{
			float minU = (float)(x * TileInfo::tileWidth) / (float)tilesetWidth;
			float maxU = (float)(x * TileInfo::tileWidth + TileInfo::tileWidth) / (float)tilesetWidth;
			float minV = 1.0f - (float)(y * TileInfo::tileHeight + TileInfo::tileHeight) / (float)tilesetHeight;
			float maxV = 1.0f - (float)(y * TileInfo::tileHeight) / (float)tilesetHeight;

			float* uvVertices = new float[8]
			{
				minU, minV,
				minU, maxV,
				maxU, maxV,
				maxU, minV
			};

			tiles[y][x].tileUVData = uvVertices;
		}
	}

	return tiles;
}

int** Tilemap::LoadTilemap(const char* tilemapPath)
{
	const int LEVEL_LOAD_CHARS_BUFFER_SIZE = 64;

	try
	{
		std::ifstream levelFile;
		int** level;
		char buffer[LEVEL_LOAD_CHARS_BUFFER_SIZE];

		float rows = tilemapHeight / TileInfo::tileHeight;
		float columns = tilemapWidth / TileInfo::tileWidth;

		levelRows = (tilemapHeight % TileInfo::tileHeight == 0) ? rows : rows + 1;
		levelColumns = (tilemapWidth % TileInfo::tileWidth == 0) ? columns : columns + 1;

		level = new int*[levelRows];
		for (int i = 0; i < levelRows; i++)
		{
			level[i] = new int[levelColumns];
		}

		std::cout << "Opening the level file..." << std::endl;
		levelFile.open(tilemapPath, std::ios::in);
		if (!levelFile.good())
		{
			throw std::ios::failure("The level file could not be opened.");
		}

		levelFile.getline(buffer, LEVEL_LOAD_CHARS_BUFFER_SIZE);
		levelFile.get(buffer, LEVEL_LOAD_CHARS_BUFFER_SIZE, '>');
		levelFile.get();

		memset(buffer, 0, sizeof(buffer));

		int x = 0;
		int y = 0;
		int nextChar = levelFile.peek();

		while (isdigit(nextChar) && !levelFile.eof())
		{
			if (x < levelColumns - 1)
			{
				levelFile.get(buffer, LEVEL_LOAD_CHARS_BUFFER_SIZE, ',');
			}
			else
			{
				if (y < levelRows - 1)
				{
					levelFile.get(buffer, LEVEL_LOAD_CHARS_BUFFER_SIZE, '\n');
				}
				else
				{
					levelFile.get(buffer, LEVEL_LOAD_CHARS_BUFFER_SIZE, '<');
				}
			}

			int digits = 0;
			int value = 0;

			for (int i = 0; buffer[i] != '\0'; i++)
			{
				digits++;
			}
			for (int i = 0; i < digits; i++)
			{
				value += ((int)buffer[i] - (int)'0') * pow(10, digits - 1 - i);
			}

			level[y][x] = value;

			if (x < levelColumns - 1)
			{
				x++;
			}
			else
			{
				x = 0;
				y++;
			}

			levelFile.get();
			nextChar = levelFile.peek();
		}

		std::cout << "The level file was read properly." << std::endl;

		return level;
	}
	catch (std::iostream::failure& exception)
	{
		std::cerr << exception.what() << std::endl;
	}
	//ifstream tilemapFile;

	//vector<std::vector<int>> tilemap;

	//float rows = tilemapHeight / TileInfo::tileHeight;
	//float columns = tilemapWidth / TileInfo::tileWidth;

	//string line;
	//string value;

	//tilemapFile.open(tilemapPath, std::ios::in);

	//if (!tilemapFile.good())
	//{
	//	throw std::ios::failure("The level file could not be opened.");
	//}

	//while (getline(tilemapFile, line))
	//{
	//	vector<int> v;              
	//	stringstream s(line);       
	//	while (getline(s, value, ','))
	//	{
	//		v.push_back(stoi(value)); 
	//	}
	//	tilemap.push_back(v);       
	//}

	//for (auto& row : tilemap)
	//{               
	//	for (auto& value : row)   
	//	{ 
	//		cout << value << "  ";
	//	}
	//	cout << "\n";                  
	//}

	//return tilemap;
}

TileInfo** Tilemap::CreateOnScreenTiles()
{
	TileInfo** onScreenTiles = new TileInfo*[screenTilesRows];

	for (int i = 0; i < screenTilesRows; i++)
		onScreenTiles[i] = new TileInfo[screenTilesColumns];

	int totalTiles = screenTilesRows * screenTilesColumns;

	float vertexBufferSize = sizeof(float) * TileInfo::VERTEX_AMOUNT * TileInfo::VERTEX_COMPONENTS * totalTiles;

	g_vertex_buffer_data = SetScreenTilesVertices(totalTiles);
	vertexBuffer = renderer->GenBuffer(vertexBufferSize, g_vertex_buffer_data);

	return onScreenTiles;
}

float* Tilemap::SetScreenTilesVertices(int totalTiles) const
{
	float* vertexBufferData = new float[TileInfo::VERTEX_AMOUNT * TileInfo::VERTEX_COMPONENTS * totalTiles];

	int counter = 0;

	for (int y = 0; y < screenTilesRows; y++)
		for (int x = 0; x < screenTilesColumns; x++)
		{
			float minX = x * TileInfo::tileWidth;
			float maxX = x * TileInfo::tileWidth + TileInfo::tileWidth;
			float minY = (float)renderer->GetRenderWindow()->GetHeight() - (float)(y * TileInfo::tileHeight + TileInfo::tileHeight);
			float maxY = (float)renderer->GetRenderWindow()->GetHeight() - (float)(y * TileInfo::tileHeight);

			float vertices[TileInfo::VERTEX_AMOUNT * TileInfo::VERTEX_COMPONENTS] =
			{
				minX, minY, 0.0f,
				minX, maxY, 0.0f,
				maxX, maxY, 0.0f,
				maxX, minY, 0.0f
			};

			for (int i = 0; i < TileInfo::VERTEX_AMOUNT * TileInfo::VERTEX_COMPONENTS; i++, counter++)
			{
				vertexBufferData[counter] = vertices[i];
			}
		}

	return vertexBufferData;
}

float* Tilemap::CreateUvBuffer() const
{
	int totalTiles = screenTilesRows * screenTilesColumns;

	float* uvBufferData = new float[TileInfo::VERTEX_AMOUNT * 2 * totalTiles];

	int counter = 0;

	float defaultUvVertices[8] =
	{
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	for (int y = 0; y < screenTilesRows; y++)
	{
		for (int x = 0; x < screenTilesColumns; x++)
		{
			for (int i = 0; i < TileInfo::VERTEX_AMOUNT * 2; i++, counter++)
			{
				uvBufferData[counter] = defaultUvVertices[i];
			}
		}
	}

	return uvBufferData;
}

void Tilemap::SetTileProperty(unsigned int tileIndex, TileType tileType)
{
	try
	{
		if (tileIndex > tilesetRows * tilesetColumns)
		{
			throw std::logic_error("Could not set the tile property because the tile index is out of range.");
		}

		unsigned int row = tileIndex / tilesetRows;
		unsigned int column = tileIndex % tilesetColumns;

		tiles[row][column].tileType = tileType;

		glm::vec2 tilingOffset((int)vectorPosition.x / TileInfo::tileWidth, (int)vectorPosition.y / TileInfo::tileHeight);

		int lastRow = (int)tilemapHeight / (int)TileInfo::tileHeight - 1;
		int lastColumn = (int)tilemapWidth / (int)TileInfo::tileWidth - 1;

		for (int y = 0; y < screenTilesRows; y++)
		{
			for (int x = 0; x < screenTilesColumns; x++)
			{
				int levelRow = glm::min(y + (int)tilingOffset.y, lastRow);
				int levelColumn = glm::min(x + (int)tilingOffset.x, lastColumn);

				if (tilemap[levelRow][levelColumn] == tileIndex)
				{
					onScreenTiles[y][x].tileType = tileType;
				}
			}
		}
	}
	catch (std::logic_error& exc)
	{
		std::cerr << exc.what() << std::endl;
	}
}

void Tilemap::UpdateVerticesUV()
{
	int totalTiles = screenTilesRows * screenTilesColumns;
	int uvBufferSize = sizeof(float) * TileInfo::VERTEX_AMOUNT * 2 * totalTiles;

	glm::vec2 tilingOffset((int)vectorPosition.x / TileInfo::tileWidth, (int)vectorPosition.y / TileInfo::tileHeight);
	int lastRow = (int)tilemapHeight / (int)TileInfo::tileHeight - 1;
	int lastColumn = (int)tilemapWidth / (int)TileInfo::tileWidth - 1;

	int counter = 0;

	for (int y = 0; y < screenTilesRows; y++)
	{
		for (int x = 0; x < screenTilesColumns; x++)
		{
			int levelRow = glm::min(y + (int)tilingOffset.y, lastRow);
			int levelColumn = glm::min(x + (int)tilingOffset.x, lastColumn);

			TileInfo tile = GetTile(tilemap[levelRow][levelColumn]);

			onScreenTiles[y][x].tileType = tile.tileType;

			for (int i = 0; i < TileInfo::VERTEX_AMOUNT * 2; i++, counter++)
			{
				g_uv_buffer_data[counter] = tile.tileUVData[i];
			}
		}
	}

	uvBuffer = renderer->GenUVBuffer(uvBufferSize, g_uv_buffer_data);
}

void Tilemap::ScrollView(float x, float y)
{
	float screenOffsetX = renderer->GetRenderWindow()->GetWidth();
	float screenOffsetY = renderer->GetRenderWindow()->GetHeight();
	float translateX = 0.0f;
	float translateY = 0.0f;

	if (vectorPosition.x + accumTrans.x + x < tilemapWidth - screenOffsetX)
	{
		translateX = (vectorPosition.x + accumTrans.x + x > 0.0f) ? x : -(vectorPosition.x + accumTrans.x);
	}
	else
	{
		translateX = tilemapWidth - screenOffsetX - vectorPosition.x - accumTrans.x;
	}

	if (vectorPosition.y + accumTrans.y + y < tilemapHeight - screenOffsetY)
	{
		translateY = (vectorPosition.y + accumTrans.y + y > 0.0f) ? y : -(vectorPosition.y + accumTrans.y);
	}
	else
	{
		translateY = tilemapHeight - screenOffsetY - vectorPosition.y - accumTrans.y;
	}

	accumTrans.x += translateX;
	accumTrans.y += translateY;

	float accumTransX = abs(accumTrans.x);
	float accumTransY = abs(accumTrans.y);

	if (accumTransX >= TileInfo::tileWidth || accumTransY >= TileInfo::tileHeight)
	{
		if (accumTransX >= TileInfo::tileWidth)
		{
			Translate(vectorPosition.x + (glm::sign(accumTrans.x) * (int)TileInfo::tileWidth), vectorPosition.y/*0.0f*/, vectorPosition.z/*0.0f*/);
			accumTrans.x -= glm::sign(accumTrans.x) * (int)TileInfo::tileWidth;
		}

		if (accumTransY >= TileInfo::tileHeight)
		{
			Translate(/*0.0f*/vectorPosition.x, vectorPosition.y + (glm::sign(accumTrans.y) * (int)TileInfo::tileHeight), vectorPosition.z/*0.0f*/);
			accumTrans.y -= glm::sign(accumTrans.y) * (int)TileInfo::tileWidth;
		}

		UpdateVerticesUV();
	}

	renderer->UpdateView(vectorPosition.x + accumTrans.x, vectorPosition.y + accumTrans.y);
}

TileInfo Tilemap::GetTile(unsigned int tileIndex) const
{
	try
	{
		if (tileIndex >= tilesetRows * tilesetColumns)
		{
			throw std::logic_error("The tile index is out of the tileset range.");
		}

		unsigned int column = tileIndex % tilesetColumns;
		unsigned int row = tileIndex / tilesetRows;

		return tiles[row][column];
	}
	catch (std::logic_error& exc)
	{
		std::cerr << exc.what() << std::endl;
	}
}

TileType Tilemap::GetTileType(unsigned int row, unsigned int column) const
{
	try
	{
		if (row >= levelRows || (int)row < 0 || column >= levelColumns || (int)column < 0)
		{
			throw std::logic_error("The tile that is trying to be accessed is out of the level boundaries.");
		}

		return GetTile(tilemap[row][column]).tileType;
	}
	catch (std::logic_error& exc)
	{
		std::cerr << exc.what() << std::endl;
	}
}

glm::vec2 Tilemap::WorldToGrid(float posX, float posY) const
{
	unsigned int row = (levelRows - 1) - (int)posY / TileInfo::tileHeight;
	unsigned int col = posX / TileInfo::tileWidth;

	return glm::vec2(row, col);
}

glm::vec2 Tilemap::GridToWorld(unsigned int row, unsigned int col) const
{
	float posX = col * TileInfo::tileWidth;
	float posY = -((int)(row - levelRows + 1) * (int)TileInfo::tileHeight) + lastRowOffset;

	return glm::vec2(posX, posY);
}

void Tilemap::Draw()
{
	renderer->LoadIdentityMatrix();
	renderer->SetModelMatrix(model);

	if (material != nullptr)
	{
		material->Bind();
		renderer->BindTexture(texture);
		material->SetMatrixProperty(renderer->GetMVP());
		material->SetTextureProperty();
	}

	renderer->EnableBlend();

	renderer->EnableAttributes(0);
	renderer->EnableAttributes(1);
	renderer->BindBuffer(vertexBuffer, 0);
	renderer->BindUVBuffer(uvBuffer, 1);
	renderer->DrawBuffer(QUAD, TileInfo::VERTEX_AMOUNT * screenTilesRows * screenTilesColumns);

	renderer->DisableAttributes(0);
	renderer->DisableAttributes(1);

	renderer->DisableBlend();
}

Tilemap::~Tilemap()
{
	renderer->DestroyBuffer(vertexBuffer);
	renderer->DestroyBuffer(uvBuffer);
	delete[] g_vertex_buffer_data;
	delete[] g_uv_buffer_data;

	for (int i = 0; i < tilesetRows; i++)
	{
		delete[] tiles[i]->tileUVData;
		delete[] tiles[i];
	}
	delete[] tiles;

	for (int i = 0; i < screenTilesRows; i++)
	{
		delete[] onScreenTiles[i];
	}
	delete[] onScreenTiles;

	for (int i = 0; i < levelRows; i++)
	{
		delete[] tilemap[i];
	}
	delete[] tilemap;
}
