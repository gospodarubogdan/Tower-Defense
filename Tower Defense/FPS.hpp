#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class FPS
{
public:
	FPS();

	void update(sf::Time dt);
	void draw(sf::RenderWindow &window);

	void setFont(const sf::Font &font);

	const unsigned int getFPS() const;

private:
	unsigned int frames;
	unsigned int fps;
	sf::Time updateTime;

	sf::Text fpsText;
};