#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Game.h"
#include "AreaMap.h"

class Player : public Entity
{
public:
	Player(GameDataRef data, AreaMap& curMap, bool def = true);
	~Player();
	void Update(float dt);
	void Draw();
	void Init(bool def);
	void SetDirection(const sf::Vector2f& dir);
	void SetPos(sf::Vector2f newPos);
private:
	GameDataRef _data;
	AreaMap& m_curMapRef;
	std::vector<Animation> m_animations;
};

