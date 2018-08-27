#include "AreaMap.h"



AreaMap::AreaMap()
{
}

void AreaMap::Init(int width, int height)
{
	_mapWidth = BEGINNING_MAP_WIDTH;
	_mapHeight = BEGINNING_MAP_HEIGHT;
	for (int i = 0; i < _mapHeight; i++)
	{
		for (int j = 0; j < _mapWidth; j++)
		{
			_tiles.at(i * _mapHeight + j).y = i * 64;
			_tiles.at(i * _mapHeight + j).x = j * 128;
			_tiles.at(i * _mapHeight + j)._isWall = false;
			_tiles.at(i * _mapHeight + j)._tType = TileType::One;
		}
	}
}

std::vector<Tile>& AreaMap::GetTiles()
{
	return _tiles;
}