#pragma once

#include "System.hpp"
#include <SFML/System.hpp>

class DrawSystem : public System
{
public:
	DrawSystem();
	~DrawSystem() = default;

	void update(sf::Time dt) override;
	void draw(sf::RenderWindow &window);
};

