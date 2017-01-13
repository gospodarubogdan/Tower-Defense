#include "AISystem.hpp"
#include "Entity.hpp"
#include "ComponentsData.hpp"
#include "EntityManager.hpp"

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
		sf::RectangleShape shape;
		shape.setSize({ 10, 10 });
		shape.setOrigin(5, 5);
		shape.setPosition(x, y);

		checkpoints.push_back(shape);
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
	if (entities.empty())
	{
		manager->getLevelData().levelOver = true;
		return;
	}

	for (auto &entity : entities)
	{
		auto position = static_cast<PositionComponent*>(entity->getComponent(Components::ID::PositionComponent));
		auto velocity = static_cast<VelocityComponent*>(entity->getComponent(Components::ID::VelocityComponent));
		auto ai = static_cast<AIComponent*>(entity->getComponent(Components::ID::AIComponent));
		auto dir      = static_cast<DirectionComponent*>(entity->getComponent(Components::ID::DirectionComponent));
		auto hp = static_cast<HealthComponent*>(entity->getComponent(Components::ID::HealthComponent));
		
		if (checkpointReached(position->x, position->y, ai->index))
			ai->index++;

		if (ai->index == CHECKPOINTS)
		{
			manager->getGameData().lives--;
			manager->requestEntityRemoval(entity->getID());
			continue;
		}

		velocity->duration += dt;
		if (velocity->duration.asSeconds() >= 2.f)
		{
			velocity->duration = sf::Time::Zero;
			velocity->speed = manager->getLevelData().movementSpeed;
		}

		int index = ai->index;
		sf::Vector2f checkpointPos = checkpoints[index].getPosition();
		sf::Vector2f direction(checkpointPos.x - position->x, checkpointPos.y - position->y);

		float magnitude = sqrt((direction.x * direction.x) + (direction.y * direction.y));
		sf::Vector2f unitVector(direction.x / magnitude, direction.y / magnitude);
	
		updateDirection(dir, unitVector);
		moveEntity(position->x, position->y, dir, velocity->speed * dt.asSeconds());

		hp->healthBar.setPosition(position->x - 16, position->y - 26);
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

void AISystem::moveEntity(float &x, float &y, DirectionComponent *direction, float factor)
{
	switch (direction->dir)
	{
	case Direction::Up:
		y -= factor;
		break;
	case Direction::Down:
		y += factor;
		break;
	case Direction::Left:
		x -= factor;
		break;
	case Direction::Right:
		x += factor;
		break;
	}
}

bool AISystem::checkpointReached(float x, float y, int index)
{
	return checkpoints[index].getGlobalBounds().contains({x, y});
}
