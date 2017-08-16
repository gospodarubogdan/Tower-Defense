#pragma once

#include <SFML/Graphics.hpp>

class FPS
{
public:
	FPS();

	void update(sf::Time dt);
	void draw(sf::RenderWindow &window) const;

	void setFont(const sf::Font &font);

	unsigned int getFPS() const;

private:
	unsigned int frames;
	unsigned int fps;
	sf::Time updateTime;

	sf::Text fpsText;
};