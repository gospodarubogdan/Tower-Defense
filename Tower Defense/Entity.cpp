#include "Entity.hpp"
#include "EntityManager.hpp"

Entity::Entity(EntityManager &manager, unsigned int ID)
	: manager(&manager)
	, ID(ID)
{
}

const unsigned int Entity::getID() const
{
	return ID;
}

bool Entity::hasComponent(Components::ID component)
{
	return false;
}

void Entity::addComponent(Components::ID component)
{
	//componentBits.flip(component);

	manager->addComponent(*this, component);
}

void Entity::removeComponent(Components::ID component)
{
	manager->removeComponent(*this, component);
}

Component *Entity::getComponent(Components::ID component)
{
	return manager->getComponent(*this, component);
}
