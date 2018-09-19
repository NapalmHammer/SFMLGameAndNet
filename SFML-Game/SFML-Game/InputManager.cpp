#include "InputManager.h"

void InputManager::UpdateInput(sf::Event e)
{

	if (sf::Event::KeyPressed == e.type)
	{
		OnKeyPress(e.key.code);
	}
	else if (e.type == sf::Event::KeyReleased)
	{
		OnKeyRelease(e.key.code);
	}
}

void InputManager::OnKeyPress(sf::Keyboard::Key key)
{
	keys[key] = true;
}

void InputManager::OnKeyRelease(sf::Keyboard::Key key)
{
	keys[key] = false;
}

bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow & window)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		sf::IntRect tempRect((int)object.getPosition().x, (int)object.getPosition().y, (int)object.getGlobalBounds().width, (int)object.getGlobalBounds().height);

		if (tempRect.contains(sf::Mouse::getPosition(window)))
		{
			return true;
		}
	}
	return false;
}

bool InputManager::GetButtonPressed(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}

bool InputManager::IsKeyPressed(sf::Keyboard::Key key)
{
	return keys[key];
}

sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow & window)
{
	return sf::Mouse::getPosition(window);
}
