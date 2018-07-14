#include "Log.h"

Log::Log()
{
	m_Font.loadFromFile("OpenSans-Regular.ttf");
	m_Text.setFont(m_Font);	
}

void Log::Draw(sf::RenderTarget & t)
{
	auto CharSize = m_Text.getCharacterSize();
	for (int i = 0; i < m_MessageBuffer.size(); i++)
	{
		m_Text.setPosition({ 0, CharSize + CharSize * (float)i});
		m_Text.setString(m_MessageBuffer[i]);
		t.draw(m_Text);
	}
}

void Log::AppendLog(std::string s)
{
	m_MessageBuffer.push_back(s);
	if (m_MessageBuffer.size() > m_MsgHistory)
		PopLog();
}

void Log::PopLog()
{
	m_MessageBuffer.erase(m_MessageBuffer.begin());
}

std::vector<std::string>& Log::GetLog()
{
	return m_MessageBuffer;
}
