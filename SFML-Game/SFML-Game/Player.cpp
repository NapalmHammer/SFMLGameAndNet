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
	m_animations[int(this->m_Direction)].Update(dt);
	m_animations[int(this->m_Direction)].ApplyToSprite(this->m_sprite);
	// Handle setting direction and velocity based on keyboard input
	if (this->_data->input.keys[sf::Keyboard::Up])
	{
		if (this->_data->input.keys[sf::Keyboard::Right])
		{
			this->SetDirection(Direction::NE);
			this->SetVelocity({ 1.0f,-1.0f });
		}
		else if (this->_data->input.keys[sf::Keyboard::Left])
		{
			this->SetDirection(Direction::NW);
			this->SetVelocity({ -2.0f,-2.0f });
		}
		else
		{
			this->SetDirection(Direction::N);
			this->SetVelocity({ 0.0f,-2.0f });
		}
	}
	else if (this->_data->input.keys[sf::Keyboard::Down])
	{
		if (this->_data->input.keys[sf::Keyboard::Right])
		{
			this->SetDirection(Direction::SE);
			this->SetVelocity({ 2.0f,2.0f });
		}
		else if (this->_data->input.keys[sf::Keyboard::Left])
		{
			this->SetDirection(Direction::SW);
			this->SetVelocity({ -1.0f,1.0f });
		}
		else
		{
			this->SetDirection(Direction::S);
			this->SetVelocity({ 0.0f,2.0f });
		}
	}
	else if (this->_data->input.keys[sf::Keyboard::Left])
	{
		this->SetDirection(Direction::W);
		this->SetVelocity({ -2.0f,0.0f });
	}
	else if (this->_data->input.keys[sf::Keyboard::Right])
	{
		this->SetDirection(Direction::E);
		this->SetVelocity({ 2.0f,0.0f });
	}
	else
	{
		this->SetVelocity({ 0.0f,0.0f });
		this->m_sprite.setTextureRect({ 0, (1 + (int)this->m_Direction) * 64,this->m_spriteSize.x, this->m_spriteSize.y });
	}
	//--

	//handle amplifying speed with the Space bar
	if (this->_data->input.keys[sf::Keyboard::Space])
	{
		speed = 2.0f;
	}
	else
	{
		speed = 1.0f;
	}

	if (this->_data->input.keys[sf::Keyboard::Escape])
	{
		this->_data->window.close();
	}
	//--

	// Handle the actual movement of the character
	TryMove(m_Velocity); // Attempt the move, based on the velocity of the character

		// normal setting the texture rect of the character, calculating cartesian position, and scale
	m_sprite.setPosition(GetCartesianPos(m_Pos));
	m_sprite.setScale(_data->_scale);
		//--
	//--

	// Outputing information for debugging
	//std::cout << this->_data->input.keys[sf::Keyboard::Up] <<
	//	", " << this->_data->input.keys[sf::Keyboard::Down] <<
	//	", " << this->_data->input.keys[sf::Keyboard::Left] <<
	//	", " << this->_data->input.keys[sf::Keyboard::Right] <<
	//	"\n";

	//--
}

void Player::Draw()
{		
	_data->window.draw(m_sprite);
	//std::cout << "X " << m_Pos.x << " Y " << m_Pos.y << std::endl;
}

void Player::Init(bool def)
{
	this->_data->assets.LoadTexture("Default char texture", DEFAULT_PLAYER_TEXTURE_FILEPATH);
	this->m_sprite.setTexture(this->_data->assets.GetTexture("Default char texture"));
	if (def)
	{
		for (int i = 0; i < 8; i++)
		{
			Animation temp(0, 64 + (i * 64), 64, 64, (this->_data->assets.GetTexture("Default char texture")), 8, 0.05f);
			m_animations.push_back(temp);
		}
		speed = 1.0f;
		m_Direction = Direction::SE;
		m_Velocity = { 0.0f, 0.0f };
		this->m_Pos = this->m_curMapRef.GetSpawnPoint();
		this->m_spriteSize = { 64, 64 };
		this->m_sprite.setTextureRect({ 0,0 + 3 * 64,m_spriteSize.x, m_spriteSize.y });
	}
}

void Player::SetDirection(const Direction Dir)
{
	m_Direction = Dir;
}

void Player::SetVelocity(sf::Vector2f vel)
{
	m_Velocity = vel * speed;
}

void Player::SetPos(sf::Vector2f newPos)
{
	this->m_Pos = newPos;
}

void Player::TryMove(sf::Vector2f pos)
{	
	sf::Vector2f temp;
	if (this->m_curMapRef.GetMapDimensions().contains(sf::Vector2i(this->m_Pos + pos)))
	{
		this->m_Pos += pos;

		temp = pos;
	}
	else
	{
		if (this->m_curMapRef.GetMapDimensions().contains(sf::Vector2i(this->m_Pos + sf::Vector2f(pos.x, 0))))
		{
			if (pos.y == 1.0f * this->speed || pos.y == -1.0f * this->speed)
			{
				this->m_Pos += sf::Vector2f((pos.x * 2), 0);
				temp.x = pos.x * 2;
			}
			else
			{
				this->m_Pos += sf::Vector2f(pos.x, 0);
				temp.x = pos.x;
			}
		}
	
		if (this->m_curMapRef.GetMapDimensions().contains(sf::Vector2i(this->m_Pos + sf::Vector2f(0, pos.y))))
		{
			if (pos.x == 1.0f * this->speed|| pos.x == -1.0f * this->speed)
			{
				this->m_Pos += sf::Vector2f(0, (pos.y * 2));
				temp.y = pos.y * 2;
			}
			else
			{
				this->m_Pos += sf::Vector2f(0, pos.y);
				temp.y = pos.y;
			}
		}
	}

	std::cout << "Velocit: " << "x: " << temp.x << " y: " << temp.y << std::endl;
}

sf::Vector2f Player::GetCartesianPos(sf::Vector2f vec)
{
	sf::Vector2f CartesianPos = { vec.x * _data->_scale.x, vec.y * _data->_scale.y };
	CartesianPos = _data->transform.transformPoint(CartesianPos);
	CartesianPos.y /= 2;
	CartesianPos -= {32.0f * _data->_scale.x, 32.0f * _data->_scale.y}; // Need to automate number handling instead of hard coding sprite dimensions
	return CartesianPos;
}
