#include "Player.h"



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
	sf::Vector2f tempPos = temp.transformPoint(m_Pos);
	tempPos.y = tempPos.y / 2;
	m_sprite.setPosition(tempPos);
	_data->window.draw(m_sprite);
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
