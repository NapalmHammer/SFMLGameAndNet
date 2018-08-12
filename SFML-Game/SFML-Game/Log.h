#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Log
{
public:
	Log();
	void Draw(sf::RenderTarget& t);
	void AppendLog(std::string s);
	void PopLog();
	std::vector<std::string>& GetLog();
private:
	int m_MsgHistory = 5;
	sf::Font m_Font;
	sf::Text m_Text;
	std::vector<std::string> m_MessageBuffer;
};