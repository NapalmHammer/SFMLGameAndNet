#pragma once
#include <SFML/Graphics.hpp>
#include "Log.h"
#include "InputConsole.h"

class ChatWindow
{
public:
	ChatWindow();
	void Begin();
	void Update();
	void Compose();
	void End();
private:
	Log m_Log;
	InputConsole m_Console;
	sf::RenderWindow m_ChatWindow;
};