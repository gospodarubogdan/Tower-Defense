#pragma once

#include "System.hpp"

class Entity;

class ShootSystem : public System
{
public:
	ShootSystem();
	~ShootSystem() = default;

	void update(sf::Time dt) override;

private:
	void selectTarget(const sf::CircleShape &range, Entity *&target);
	void createProjectile(Entity *turret, float x, float y, Entity *target);
	bool isTargetInRange(const sf::CircleShape &range, Entity *target);
};

