#include <sstream>
#include "GameState.h"
#include "DEFINITIONS.h"
#include <iostream>

GameState::GameState(GameDataRef data)
	:_data(data),
	_beginningMap(data)
{

}

void GameState::Init()
{
	gameState = STATE_PLAYING;

	//this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);

	this->_background.setTexture(this->_data->assets.
		GetTexture("Background"));

	//_background.setTexture(this->_data->assets.
	//		GetTexture("Pause Button"));


	//_pauseButton.setPosition(this->_data->window.getSize().x -
	//	_pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);
}

void GameState::HandleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}
		//if (this->_data->input.IsSpriteClicked(this->
		//	_pauseButton, sf::Mouse::Left, this->_data->window))
		//{
		//	std::cout << "Pause the game" << std::endl;
		//}
	}
}

void GameState::Update(float dt)
{

}

void GameState::Draw(float dt)
{
	this->_data->window.clear();

	this->_data->window.draw(this->_background);
	this->_beginningMap.Draw();
	//this->_data->window.draw(this->_pauseButton);

	this->_data->window.display();
}
