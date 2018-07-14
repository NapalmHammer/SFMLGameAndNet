#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Log.h"

class InputConsole
{
public:
	InputConsole();
	void Update(sf::Event& e, Log& l);
	void Compose();
	void End(sf::RenderTarget& w);
private:
	sf::Font m_Font;
	sf::Text m_Text;
	std::string m_StrBuf;
};