#pragma once

#include "ComponentsID.hpp"
#include "Component.hpp"

#include <unordered_map>

class EntityManager;

class Entity
{
public:
	explicit Entity(EntityManager &manager, unsigned int ID);

	Entity() = default;
	~Entity() = default;

	Entity(const Entity&) = delete;
	Entity(Entity&&) = default;
	Entity& operator=(const Entity&) = delete;
	Entity& operator=(Entity&&) = default;

	unsigned int getID() const;

	bool hasComponent(Components::ID component) const;

	void addComponent(Components::ID component);
	void removeComponent(Components::ID component);
	void clearComponents();

	Component *getComponent(Components::ID component);
	int getBits() const;

private:
	EntityManager *manager;
	unsigned int ID;
	int componentBits;

	std::unordered_map<Components::ID, Component::Ptr> components;
};