#pragma once
#include <SFML/Graphics.hpp>

class InputManager
{
public:
	InputManager() {};
	~InputManager() {};

	void UpdateInput(sf::Event e);
	void OnKeyPress(sf::Keyboard::Key key);
	void OnKeyRelease(sf::Keyboard::Key key);
	bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);
	bool GetButtonPressed(sf::Keyboard::Key key);
	bool IsKeyPressed(sf::Keyboard::Key key);
	sf::Vector2i GetMousePosition(sf::RenderWindow& window);


	bool keys[sf::Keyboard::KeyCount];
};