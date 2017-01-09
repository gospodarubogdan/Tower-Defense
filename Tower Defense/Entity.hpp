#pragma once

#include <bitset>

#include "ComponentsID.hpp"

class EntityManager;
class Component;

class Entity
{
public:
	explicit Entity(EntityManager &manager, unsigned int ID);

	Entity() = default;
	~Entity() = default;

	Entity(const Entity&) = default;
	Entity(Entity&&) = default;
	Entity& operator=(const Entity&) = default;
	Entity& operator=(Entity&&) = default;

	const unsigned int getID() const;

	bool hasComponent(Components::ID component);

	void addComponent(Components::ID component);
	void removeComponent(Components::ID component);

	Component *getComponent(Components::ID component);

private:
	EntityManager *manager;
	unsigned int ID;
	std::bitset<MAX_COMPONENTS> componentBits;
};