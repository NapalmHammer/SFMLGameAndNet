#pragma once
#include "DEFINITIONS.h"
#include <vector>

enum TileType
{
	One,
	two,
	three,
	four,
	five
};

struct Tile
{
	bool _isWall = false;
	TileType _tType = TileType::One;
	int x = 0;
	int y = 0;
};

class AreaMap
{
public:
	AreaMap();

	void Init(int width, int height );
	std::vector<Tile>& GetTiles();
private:
	std::vector<Tile> _tiles;
	int _mapWidth;
	int _mapHeight;
};

