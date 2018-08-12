#include "ChatWindow.h"

ChatWindow::ChatWindow()
	:m_ChatWindow(sf::VideoMode(600, 400), "Chat/Network")
{
}

void ChatWindow::Begin()
{
	m_ChatWindow.clear();
}

void ChatWindow::Update()
{
	sf::Event event;
	while (m_ChatWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_ChatWindow.close();
		}
		else if (event.type == sf::Event::TextEntered)
		{
			m_Console.Update(event, m_Log);
		}
	}
}

void ChatWindow::Compose()
{
	m_Console.Compose();
}

void ChatWindow::End()
{
	m_Console.End(m_ChatWindow);
	m_Log.Draw(m_ChatWindow);

	// THIS MUST ALWAYS RUN LAST
	m_ChatWindow.display();
}
