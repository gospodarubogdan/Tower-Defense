#pragma once

#include <SFML/Graphics.hpp>	
#include "Component.hpp"

enum class Direction : int
{
	Up = 0,
	Down = 1,
	Left = 2,
	Right = 3
};

class PositionComponent : public Component
{
public:
	float x, y;
};

class VelocityComponent : public Component
{
public:
	float speed;
	sf::Time duration;
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

class HealthComponent : public Component
{
public:
	int health;
	//sf::Sprite healthBar;
	sf::RectangleShape healthBar;
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

class BoundComponent : public Component
{
public:
	sf::RectangleShape box;
};

class DirectionComponent : public Component
{
public:
	Direction dir;
	bool changed;
};

class AnimationComponent : public Component
{
public:
	int frame;
	sf::Time elapsedTime;
};

class SplashComponent : public Component
{
public:
	float range;
};

class SlowComponent : public Component
{
public:
	float speed;
};