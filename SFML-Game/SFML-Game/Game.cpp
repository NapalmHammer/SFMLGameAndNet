#include "Game.h"

Game::Game(int width, int height, std::string title)
{
	_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);

	_data->shape.setRadius(100.0f);
	_data->shape.setFillColor(sf::Color::Green);

	this->Go();
}

void Game::Go()
{
	float newTime, frameTime, interpolation;
	float currentTime = this->_clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (this->_data->window.isOpen())
	{
		this->_data->m_fsm.ProcessStateChanges();
		newTime = this->_clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			this->_data->m_fsm.GetActiveState()->HandleInput();
			this->_data->m_fsm.GetActiveState()->Update(dt);

			accumulator -= dt;
			this->_data->m_fsm.GetActiveState()->Draw(interpolation);
		}

		interpolation = accumulator / dt;

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
