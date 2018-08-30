#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include "Game.h"
#include <vector>

enum TileType
{
	EMPTY,
	One,
	two,
	three,
	four,
	five
};

//struct Tile
//{
//	bool _isWall = false;
//	TileType _tType = TileType::EMPTY;
//	int x = 0;
//	int y = 0;
//};

class AreaMap
{
public:
	AreaMap(GameDataRef data);

	void Init(int width, int height );
	void Draw();
	//std::vector<Tile>& GetTiles();
private:
	sf::Sprite GetTileTextureRect(int it);
	//std::vector<Tile> _tiles;
	sf::Sprite _tileSprites;
	GameDataRef _data;
	int _mapWidth;
	int _mapHeight;
	int _map[BEGINNING_MAP_WIDTH * BEGINNING_MAP_HEIGHT] = {	1,1,1,1,1,1,1,1,1,1,
																1,0,0,0,0,0,0,0,0,1,
																1,0,1,1,1,1,1,1,0,1,
																1,0,1,1,1,1,1,1,0,1,
																1,0,1,1,1,1,1,1,0,1,
																1,0,1,1,1,1,1,1,0,1,
																1,0,1,1,1,1,1,1,0,1,
																1,0,1,1,1,1,1,1,0,1,
																1,0,0,0,0,0,0,0,0,1,
																1,1,1,1,1,1,1,1,1,1 };
};

