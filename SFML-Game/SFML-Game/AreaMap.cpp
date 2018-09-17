#include "AreaMap.h"



AreaMap::AreaMap(GameDataRef data, sf::Vector2f spawnPointSet)
	:_data(data),
	m_spawPoint(spawnPointSet)
{

	Init(0,0);
}

void AreaMap::Init(int width, int height)
{
	this->_data->assets.LoadTexture("Tiles", TILES_FILEPATH);
	this->_tileSprites.setTexture(this->_data->assets.GetTexture("Tiles"));

	_mapWidth = BEGINNING_MAP_WIDTH;
	_mapHeight = BEGINNING_MAP_HEIGHT;

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
				sf::Vector2f tileCartesianXY({ ((float)j * 90.0f) * this->_data->_scale.x, ((float)i * 90.0f) * this->_data->_scale.y });

				sf::Transform transform = this->_data->rotation * this->_data->translation;

				tileCartesianXY = transform.transformPoint(tileCartesianXY);
				tileCartesianXY.y /= 2;

				sf::CircleShape shape(10.0f);
				shape.setPosition(tileCartesianXY.x + 64.0f - 10.0f, tileCartesianXY.y - 10.0f);
				shape.setFillColor(sf::Color(150, 50, 250));

				temp.setPosition(tileCartesianXY);
				this->_data->window.draw(temp);
				this->_data->window.draw(shape);
			}

		}
	}
}

void AreaMap::Update(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Left)
	{
		this->_data->translation.translate({ 10.0f,0.0f });
	}
	else if (key == sf::Keyboard::Right)
	{
		this->_data->translation.translate({ -10.0f,0.0f });
	}
	else if (key == sf::Keyboard::Up)
	{
		this->_data->_scale += {0.1f, 0.1f};
	}
	else if (key == sf::Keyboard::Down)
	{
		this->_data->_scale -= {0.1f, 0.1f};
	}
	else if (key == sf::Keyboard::Escape)
	{
		this->_data->window.close();
	}
}

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
	_tileSprites.setScale(this->_data->_scale);
	return _tileSprites;
}


class A
{
public:
	A(int v)
		:black(v)
	{

	}
	int black;
};


class B
{
public:
	B(int v)
	{
		black = v;
	}
	int black;
};
