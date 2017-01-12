#pragma once

#include "System.hpp"

class ShootSystem : public System
{
public:
	ShootSystem();
	~ShootSystem() = default;

	void update(sf::Time dt) override;

private:
	void selectTarget(const sf::CircleShape &range, Entity *&target);
	void createProjectile(int x, int y, Entity *target);
	bool isTargetInRange(const sf::CircleShape &range, Entity *target);
};

