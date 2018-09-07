#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Game.h"
#include "AreaMap.h"

class Player
{
public:
	Player();
	~Player();
	void Update(float dt);
	void Draw();
	void SetDirection(const sf::Vector2f& dir);
private:
	Entity m_PlayerEntity;
	GameDataRef _data;
	AreaMap& m_mapRef;
	Animation m_RightWalk;
};

