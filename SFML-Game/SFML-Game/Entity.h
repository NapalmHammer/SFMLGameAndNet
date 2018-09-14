#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
class Entity
{
public:
	std::shared_ptr<sf::Texture> m_entityTex;
	sf::Sprite m_sprite;
	sf::Vector2f m_Pos;
	sf::Vector2f m_vel;
	sf::Vector2i m_spriteSize;
	float speed;
};

