#pragma once
#include <SFML/Graphics.hpp>
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
};