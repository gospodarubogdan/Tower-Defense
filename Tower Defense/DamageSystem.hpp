#pragma once

#include "System.hpp"

class DamageSystem : public System
{
public:
	DamageSystem();
	~DamageSystem() = default;

	void update(sf::Time dt) override;

private:
	bool isCollision(Entity *projectile, Entity *target);
};

