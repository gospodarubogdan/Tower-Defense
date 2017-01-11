#include "MoveSystem.hpp"
#include "Entity.hpp"
#include "ComponentsData.hpp"

MoveSystem::MoveSystem()
{
	bitset |= Components::ID::PositionComponent;
	bitset |= Components::ID::VelocityComponent;
	bitset |= Components::ID::TargetComponent;
}

void MoveSystem::update(sf::Time dt)
{
	for (auto &entity : entities)
	{
		auto position = static_cast<PositionComponent*>(entity->getComponent(Components::ID::PositionComponent));
		auto velocity = static_cast<VelocityComponent*>(entity->getComponent(Components::ID::VelocityComponent));
		auto target   = static_cast<TargetComponent*>(entity->getComponent(Components::ID::TargetComponent));

		auto targetPos = static_cast<PositionComponent*>(target->target->getComponent(Components::ID::PositionComponent));

		sf::Vector2f direction(targetPos->x - position->x, targetPos->y - position->y);

		float magnitude = sqrt((direction.x * direction.x) + (direction.y * direction.y));
		sf::Vector2f unitVector(direction.x / magnitude, direction.y / magnitude);

		sf::Vector2f factor(unitVector * velocity->speed * dt.asSeconds());
		position->x += factor.x;
		position->y += factor.y;
	}
}