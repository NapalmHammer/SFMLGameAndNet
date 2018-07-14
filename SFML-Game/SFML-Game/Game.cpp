#include "Game.h"

Game::Game()
	:window(sf::VideoMode(400, 400), "Game")
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
	m_CWind.Begin();
}

void Game::UpdateModel()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
	m_CWind.Update();
}

void Game::Compose()
{
	window.draw(shape);
	m_CWind.Compose();
}

void Game::End()
{
	window.display();
	m_CWind.End();
}
