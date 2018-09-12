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
}

void Player::Init(bool def)
{
	this->_data->assets.LoadTexture("Default char texture", DEFAULT_PLAYER_TEXTURE_FILEPATH);
	this->m_sprite.setTexture(this->_data->assets.GetTexture("Default char texture"));
	if (def)
	{
		this->m_Pos = this->m_curMapRef.GetSpawnPoint();
	}
}

void Player::SetDirection(const sf::Vector2f & dir)
{
}

void Player::SetPos(sf::Vector2f newPos)
{
	this->m_Pos = newPos;
}
