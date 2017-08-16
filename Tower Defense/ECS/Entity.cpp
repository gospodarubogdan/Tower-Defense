#include "Entity.hpp"
#include "EntityManager.hpp"
#include <cassert>

Entity::Entity(EntityManager &manager, unsigned int ID)
	: manager(&manager)
	, ID(ID)
	, componentBits(0)
{
}

unsigned int Entity::getID() const
{
	return ID;
}

bool Entity::hasComponent(Components::ID component) const
{
	return (componentBits & static_cast<int>(component)) == static_cast<int>(component);
}

void Entity::addComponent(Components::ID component)
{
	componentBits |= component;
	
	auto found = manager->factories.find(component);
	assert(found != manager->factories.end());
	components.insert(std::make_pair(component, found->second()));

	//manager->addComponent(*this, component);
}

void Entity::removeComponent(Components::ID component)
{
	//manager->removeComponent(*this, component);
	componentBits &= ~(1 << component);
}

void Entity::clearComponents()
{
	componentBits = 1 << 0;
	components.clear();
}

Component *Entity::getComponent(Components::ID component)
{
	if(hasComponent(component))
		return components.at(component).get();
	return nullptr;
}

int Entity::getBits() const
{
	return componentBits;
}
