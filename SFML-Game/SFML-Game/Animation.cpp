#include "Animation.h"



Animation::Animation(int x, int y, int width, int height, std::shared_ptr<sf::Texture> pTex, int nframes, float holdtime)
	:m_nFrames(nframes),
	m_holdTime(holdtime)
{
	m_frames.reserve(m_nFrames);
	m_iFrame = 0;
	m_time = 0.0f;
	for (int i = 0; i < m_nFrames; i++)
	{
		m_frames[i] = { x + i * width, y, x + (i + 1) * width, y + height };
	}
}

void Animation::ApplyToSprite(sf::Sprite & s) const
{
	s.setTexture(*m_pTex);
	s.setTextureRect(m_frames[m_iFrame]);
}

void Animation::Update(float dt)
{
	m_time += dt;
	while (m_time >= m_holdTime)
	{
		m_time -= m_holdTime;
		Advance();
	}
}

void Animation::Advance()
{
	if (++m_iFrame >= m_nFrames)
	{
		m_iFrame = 0;
	}
}
