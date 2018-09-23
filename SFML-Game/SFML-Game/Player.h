#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Game.h"
#include "AreaMap.h"

enum class Direction
{
	NE,
	E,
	SE,
	S,
	SW,
	W,
	NW,
	N
};

class Player : public Entity
{
public:
	Player(GameDataRef data, AreaMap& curMap, bool def = true);
	~Player();
	void Update(float dt);
	void Draw();
	void Init(bool def);
	void SetDirection(const Direction dir);
	void SetVelocity(sf::Vector2f vel);
	void SetPos(sf::Vector2f newPos);
	void TryMove(sf::Vector2f pos);
	sf::Vector2f GetCartesianPos(sf::Vector2f pos);
private:
	float speed;
	sf::Vector2f m_Velocity;
	Direction m_Direction;
	GameDataRef _data;
	AreaMap& m_curMapRef;
	std::vector<Animation> m_animations;
};

