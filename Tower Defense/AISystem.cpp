#include "AISystem.hpp"
#include "Entity.hpp"
#include "ComponentsData.hpp"

#include <fstream>
#include <math.h>

#define CHECKPOINTS 13

AISystem::AISystem()
	: checkpoints()
{
	std::ifstream fin("checkpoints.txt");

	int x, y;
	while (fin >> x >> y)
	{
		checkpoints.push_back({ x, y });
	}
	fin.close();

	bitset |= Components::ID::PositionComponent;
	bitset |= Components::ID::VelocityComponent;
	bitset |= Components::ID::AIComponent;
	bitset |= Components::ID::DirectionComponent;
	bitset |= Components::ID::HealthComponent;
}

void AISystem::update(sf::Time dt)
{
	for (auto &entity : entities)
	{
		auto position = static_cast<PositionComponent*>(entity->getComponent(Components::ID::PositionComponent));
		auto velocity = static_cast<VelocityComponent*>(entity->getComponent(Components::ID::VelocityComponent));
		auto ai = static_cast<AIComponent*>(entity->getComponent(Components::ID::AIComponent));
		auto dir      = static_cast<DirectionComponent*>(entity->getComponent(Components::ID::DirectionComponent));
		auto hp = static_cast<HealthComponent*>(entity->getComponent(Components::ID::HealthComponent));

		if (position->x == checkpoints[ai->index].x && position->y == checkpoints[ai->index].y)
			ai->index++;

		if (ai->index == CHECKPOINTS)
			; // life--;

		int index = ai->index;
		sf::Vector2f direction(checkpoints[index].x - position->x, checkpoints[index].y - position->y);

		float magnitude = sqrt((direction.x * direction.x) + (direction.y * direction.y));
		sf::Vector2f unitVector(direction.x / magnitude, direction.y / magnitude);

		sf::Vector2f factor(unitVector * velocity->speed * dt.asSeconds());
		position->x += factor.x;
		position->y += factor.y;

		hp->healthBar.setPosition(position->x - 16, position->y - 26);

		updateDirection(dir, factor);
	}
}

void AISystem::updateDirection(DirectionComponent *direction, const sf::Vector2f &vector)
{
	auto temp = direction->dir;
	if (abs(vector.y) > abs(vector.x))
	{
		if (vector.y > 0)
			direction->dir = Direction::Down;
		else direction->dir = Direction::Up;
	}
	else
	{
		if (vector.x > 0)
			direction->dir = Direction::Right;
		else direction->dir = Direction::Left;
	}
	if (temp != direction->dir) direction->changed = true;
}
