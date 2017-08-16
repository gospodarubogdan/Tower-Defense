#pragma once

#include "System.hpp"

class MoveSystem : public System
{
public:
	MoveSystem();
	~MoveSystem() = default;

	void update(sf::Time dt) override;
};

