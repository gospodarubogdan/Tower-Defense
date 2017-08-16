#pragma once

#include "System.hpp"

class PositionComponent;

class DamageSystem : public System
{
public:
	DamageSystem();
	~DamageSystem() = default;

	void update(sf::Time dt) override;

private:
	static bool isCollision(Entity *projectile, Entity *target);
	void dealDamage(sf::Time dt, Entity *projectile) const;
	int getDistance(PositionComponent *posOne, PositionComponent *posTwo) const;

	std::vector<Entity*> enemies;
};

