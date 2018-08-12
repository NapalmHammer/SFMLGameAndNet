#include "InputConsole.h"
#include <iostream>

InputConsole::InputConsole()
{
	m_Font.loadFromFile("OpenSans-Regular.ttf");
	m_Text.setFont(m_Font);
}

void InputConsole::Update(sf::Event& e, Log& l)
{
	auto t = e.text.unicode;

	if (t == 8)
	{
		m_StrBuf.erase(m_StrBuf.end() - 1);
	}
	else if (t > 31 && t < 123)
	{
		m_StrBuf += t;
	}
	else if (t == 13)
	{
		l.AppendLog(m_StrBuf);
		m_StrBuf.clear();
	}
	else
	{
		std::cout << "unknown character: " << t << "\n";
	}
}

void InputConsole::Compose()
{
	m_Text.setString(m_StrBuf);
}

void InputConsole::End(sf::RenderTarget& w)
{
	w.draw(m_Text);
}
