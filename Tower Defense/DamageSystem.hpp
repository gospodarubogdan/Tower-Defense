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
	void addEntity(Entity &entity) override;
	void removeEntity(unsigned int id) override;

	bool isCollision(Entity *projectile, Entity *target);
	void dealDamage(sf::Time dt, Entity *projectile);
	int getDistance(PositionComponent *posOne, PositionComponent *posTwo);

	std::vector<Entity*> enemies;
};

