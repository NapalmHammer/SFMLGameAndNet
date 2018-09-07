#pragma once
#include <SFML/Graphics.hpp>
class Entity
{
public:
	Entity(sf::Vector2f pos, sf::IntRect spriteSize, bool def = true);
	~Entity();

	sf::Sprite m_sprite;
	sf::Vector2f m_Pos;
	sf::Vector2f m_vel;
	sf::IntRect m_spriteSize;
	float speed;
};

