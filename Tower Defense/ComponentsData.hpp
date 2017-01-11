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
	float speed;
};

class RangeComponent : public Component
{
public:
	sf::CircleShape range;
};

class ShootComponent : public Component
{
public:
	float attackSpeed;
	sf::Time elapsedTime;
};

class TargetComponent : public Component
{
public:
	Entity *target;
};

class RenderComponent : public Component
{
public:
	sf::Sprite sprite;
};

class TargetableComponent : public Component
{
public:
	int health;
	Entity *parent;
};

class AIComponent : public Component
{
public:
	int index;
};

class DamageComponent : public Component
{
public:
	int damage;
};