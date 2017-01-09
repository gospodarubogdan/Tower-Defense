#pragma once

#include <SFML/Graphics.hpp>	
#include "Component.hpp"

class PositionComponent : public Component
{
public:
	int x, y;
};

class VelocityComponent : public Component
{
public:
	int dx, dy;
};

class HealthComponent : public Component
{
public:
	int health;
};

class RangeComponent : public Component
{
public:
	sf::CircleShape range;
};

