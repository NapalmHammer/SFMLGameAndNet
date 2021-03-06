#pragma once
#include <SFML/Window.hpp>
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
	sf::Transform& GetScale()
	{
		return scale;
	}
	void Update(sf::Keyboard::Key key);
private:
	sf::Sprite GetTileTextureRect(int it);
	sf::Sprite _tileSprites;
	GameDataRef _data;
	int _mapWidth;
	int _mapHeight;
	int _map[BEGINNING_MAP_WIDTH * BEGINNING_MAP_HEIGHT] = {	5,5,1,1,1,1,1,1,4,4,
																5,0,0,0,3,3,0,0,0,4,
																1,0,2,2,2,2,2,2,0,1,
																1,0,2,1,1,1,1,2,0,1,
																1,3,2,1,1,1,1,2,3,1,
																1,3,2,1,1,1,1,2,3,1,
																1,0,2,1,1,1,1,2,0,1,
																1,0,2,2,2,2,2,2,0,1,
																4,0,0,0,3,3,0,0,0,5,
																4,4,1,1,1,1,1,1,5,5 };
	sf::Transform scale;
	sf::Transform translation;
	sf::Transform rotation;
	sf::Vector2f _scale;
};

