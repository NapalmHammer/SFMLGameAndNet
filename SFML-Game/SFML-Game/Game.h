#pragma once
#include "ChatWindow.h"
class Game
{
public:
	Game();
	void Go();
private:
	void Begin();
	void UpdateModel();
	void Compose();
	void End();
	sf::RenderWindow window;
	sf::CircleShape shape;
	ChatWindow m_CWind;
};