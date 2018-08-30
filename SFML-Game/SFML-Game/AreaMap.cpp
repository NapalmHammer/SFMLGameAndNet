#include "AreaMap.h"



AreaMap::AreaMap(GameDataRef data)
	:_data(data)
{
	Init(0,0);
}

void AreaMap::Init(int width, int height)
{
	this->_data->assets.LoadTexture("Tiles", TILES_FILEPATH);
	this->_tileSprites.setTexture(this->_data->assets.GetTexture("Tiles"));

	_mapWidth = BEGINNING_MAP_WIDTH;
	_mapHeight = BEGINNING_MAP_HEIGHT;
	//_tiles.reserve(BEGINNING_MAP_HEIGHT * BEGINNING_MAP_WIDTH);
	//for (int i = 0; i < _mapHeight; i++)
	//{
	//	for (int j = 0; j < _mapWidth; j++)
	//	{
	//		_tiles.at(i * _mapHeight + j).y = i * 64;
	//		_tiles.at(i * _mapHeight + j).x = j * 128;
	//		_tiles.at(i * _mapHeight + j)._isWall = false;
	//		_tiles.at(i * _mapHeight + j)._tType = TileType::One;
	//	}
	//}

}

void AreaMap::Draw()
{
	for (int i = 0; i < _mapHeight; i++)
	{
		for (int j = 0; j < _mapWidth; j++)
		{
			if (_map[i * _mapHeight + j] != 0)
			{
				sf::Sprite temp = GetTileTextureRect(i * _mapHeight + j);
				temp.setPosition({ (float)j * 128.0f, (float)i * 64.0f });
				this->_data->window.draw(temp);
			}

		}
	}
}

//std::vector<Tile>& AreaMap::GetTiles()
//{
//	return _tiles;
//}

sf::Sprite AreaMap::GetTileTextureRect(int it)
{
	switch ((TileType)it)
	{
	case TileType::One:
	{
		this->_tileSprites.setTextureRect({ 0,0,128,64 });
	}
	break;
	case TileType::two:
	{
		this->_tileSprites.setTextureRect({ 128,0,128,64 });
	}
	break;
	case TileType::three:
	{
		this->_tileSprites.setTextureRect({ 256,0,128,64 });
	}
	break;
	case TileType::four:
	{
		this->_tileSprites.setTextureRect({ 384,0,128,64 });
	}
	break;
	case TileType::five:
	{
		this->_tileSprites.setTextureRect({ 512,0,128,64 });
	}
	break;
	}
	return _tileSprites;
}
