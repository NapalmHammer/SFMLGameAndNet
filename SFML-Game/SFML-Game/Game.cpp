#include "Game.h"

Game::Game()
	:window(sf::VideoMode(200, 200), "SFML works!")
{
}

void Game::Go()
{
	shape.setRadius(100.0f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		Begin();
		UpdateModel();
		Compose();
		End();
	}
}
//----
//----------------------------------------

void Game::Begin()
{
	window.clear();
}

void Game::UpdateModel()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Game::Compose()
{
	window.draw(shape);
}

void Game::End()
{
	window.display();
}
