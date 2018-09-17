#include "Player.h"
#include <iostream>


Player::Player(GameDataRef data, AreaMap& curMap, bool def)
	:_data(data),
	m_curMapRef(curMap)
{
	Init(def);
}


Player::~Player()
{
}

void Player::Update(float dt)
{
}

void Player::Draw()
{
	sf::Transform temp = _data->rotation * _data->translation;
	sf::Vector2f CartesianPos = { m_Pos.x * _data->_scale.x, m_Pos.y * _data->_scale.y };
		
	CartesianPos = temp.transformPoint(CartesianPos);
	CartesianPos.y = CartesianPos.y / 2;
	//CartesianPos -= {32.0f * _data->_scale.x, 32.0f * _data->_scale.y};
	m_sprite.setPosition(CartesianPos);
	m_sprite.setScale(_data->_scale);
	_data->window.draw(m_sprite);

	std::cout << "X " << m_Pos.x << " Y " << m_Pos.y << std::endl;
}

void Player::Init(bool def)
{
	this->_data->assets.LoadTexture("Default char texture", DEFAULT_PLAYER_TEXTURE_FILEPATH);
	this->m_sprite.setTexture(this->_data->assets.GetTexture("Default char texture"));
	if (def)
	{
		this->m_Pos = this->m_curMapRef.GetSpawnPoint();
		//this->m_sprite.setPosition(m_Pos);
		this->m_spriteSize = { 64, 64 };
		this->m_sprite.setTextureRect({ 0,0 + 3 * 64,m_spriteSize.x, m_spriteSize.y });
	}
}

void Player::SetDirection(const sf::Vector2f & dir)
{
}

void Player::SetPos(sf::Vector2f newPos)
{
	this->m_Pos = newPos;
}
