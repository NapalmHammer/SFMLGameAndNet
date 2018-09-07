#pragma once
#include <SFML/Graphics.hpp>
class Animation
{
public:
	Animation(int x, int y, int width, int height, std::shared_ptr<sf::Texture> pTex, int nframes, float holdtime);
	void ApplyToSprite(sf::Sprite& s) const;
	void Update(float dt);

	int m_nFrames;
	int m_iFrame;
	float m_time;
	float m_holdTime;
	std::vector<sf::IntRect> m_frames;
	std::shared_ptr<sf::Texture> m_pTex;

private:
	void Advance();
};

