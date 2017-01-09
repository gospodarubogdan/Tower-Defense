#pragma once

#include "System.hpp"
#include "ComponentsData.hpp"

class MoveSystem : public System
{
public:
	MoveSystem();
	~MoveSystem() = default;

	void update(sf::Time dt) override;
	void addComponent(Entity &entity, Components::ID component) override;

private:
	std::vector<VelocityComponent*> velComponents;
	std::vector<PositionComponent*> posComponents;
};

