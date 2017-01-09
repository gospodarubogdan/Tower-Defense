#pragma once

#include "Constants.hpp"
#include "ComponentsID.hpp"

#include <SFML/Graphics.hpp>

class EntityManager;
class Entity;

class System
{
public:
	System() = default;
	virtual ~System() = default;

	virtual void update(sf::Time dt) = 0;
	virtual void addComponent(Entity &entity, Components::ID component) = 0;
	
	void setManager(EntityManager *manager);
	void setComponents(Components::ID components);

protected:
	EntityManager *manager;
	Components::ID bitset;
};