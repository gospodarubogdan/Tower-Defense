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
	bool checkpointReached(float x, float y, int index);

	std::vector<sf::RectangleShape> checkpoints;
};

