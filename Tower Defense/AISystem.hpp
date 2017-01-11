#pragma once

#include "System.hpp"

class AISystem : public System
{
public:
	AISystem();
	~AISystem() = default;

	void update(sf::Time dt) override;

private:
	std::vector<sf::Vector2i> checkpoints;
};

