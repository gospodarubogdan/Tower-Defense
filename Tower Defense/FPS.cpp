#include "FPS.hpp"



FPS::FPS()
	: frames(0)
	, fps(0)
	, updateTime(sf::seconds(0.f))
	, fpsText()
{
	fpsText.setPosition(5.f, 10.f);
	fpsText.setCharacterSize(10);
}

void FPS::update(sf::Time dt)
{
	updateTime += dt;
	frames++;

	if (updateTime.asSeconds() >= 1.f)
	{
		updateTime -= sf::seconds(1.f);
		fps = frames;
		frames = 0;

		fpsText.setString("FPS: " + std::to_string(fps));
	}
}

void FPS::draw(sf::RenderWindow &window) const
{
	window.draw(fpsText);
}

void FPS::setFont(const sf::Font &font)
{
	fpsText.setFont(font);
}

unsigned int FPS::getFPS() const
{
	return fps;
}