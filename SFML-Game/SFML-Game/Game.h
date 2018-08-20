#pragma once
#include "ChatWindow.h"
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

struct GameData
{
	sf::RenderWindow window;
	sf::CircleShape shape;
	ChatWindow m_CWind;
	StateMachine m_fsm;
	AssetManager assets;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
public:
	Game(int width, int height, std::string title);
private:
	void Go();
	void Begin();
	void UpdateModel();
	void Compose();
	void End();

	const float dt = 1.0f / 60.0f;
	sf::Clock _clock;
	GameDataRef _data = std::make_shared<GameData>();
};