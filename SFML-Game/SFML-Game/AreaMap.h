#pragma once
#include <SFML/Graphics.hpp>
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
	sf::Sprite _tileSprites;
	int _mapWidth;
	int _mapHeight;
};

