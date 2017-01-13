#pragma once

#include "System.hpp"

class DirectionComponent;

class AISystem : public System
{
public:
	AISystem();
	~AISystem() = default;

	void update(sf::Time dt) override;

private:
	void updateDirection(DirectionComponent *direction, const sf::Vector2f &vector);
	void moveEntity(float &x, float &y, DirectionComponent *direction, float factor);
	bool checkpointReached(float x, float y, int index);

	std::vector<sf::RectangleShape> checkpoints;
};

