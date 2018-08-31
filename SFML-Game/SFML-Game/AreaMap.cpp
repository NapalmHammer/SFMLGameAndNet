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
				sf::Sprite temp = GetTileTextureRect(_map[i * _mapHeight + j]);
				sf::Vector2f tileCartesianXY({ (float)j * 90.0f, (float)i * 90.0f });
				
				sf::Transform translation;
				translation.translate(650.0f, -250.0f);
				
				sf::Transform rotation;
				rotation.rotate(45);

				sf::Transform transform = rotation * translation;

				tileCartesianXY = transform.transformPoint(tileCartesianXY);
				tileCartesianXY.y /= 2;
				temp.setPosition(tileCartesianXY);
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
		this->_tileSprites.setTextureRect({ 0,0,128,82 });
	}
	break;
	case TileType::two:
	{
		this->_tileSprites.setTextureRect({ 128,0,128,82 });
	}
	break;
	case TileType::three:
	{
		this->_tileSprites.setTextureRect({ 256,0,128,82 });
	}
	break;
	case TileType::four:
	{
		this->_tileSprites.setTextureRect({ 384,0,128,82 });
	}
	break;
	case TileType::five:
	{
		this->_tileSprites.setTextureRect({ 512,0,128,82 });
	}
	break;
	}
	return _tileSprites;
}
