#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "AreaMap.h"

class GameState : public State
{
public:
	GameState(GameDataRef data);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:
	GameDataRef _data;

	sf::Sprite _background;
	AreaMap _beginningMap;

	//sf::Sprite _pauseButton;

	int turn;
	int gameState;
};
