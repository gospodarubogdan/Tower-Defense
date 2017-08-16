#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "GameContext.hpp"	

class Camera
{
public:
	explicit Camera(States::Context context);

	void handleEvent(const sf::Event &event);
	void update(sf::Time dt);
	void draw();

	const sf::View &getView() const;
private:

	sf::View view;
	States::Context context;
	sf::Vector2u windowSize;
	sf::Vector2i initialMousePos;
	bool dragging;
};

