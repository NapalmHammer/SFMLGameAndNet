#include "Entity.h"



Entity::Entity(sf::Vector2f pos, sf::IntRect spriteSize, bool def = true)
	:m_Pos(pos),
	m_spriteSize(spriteSize)
{
}


Entity::~Entity()
{
}
