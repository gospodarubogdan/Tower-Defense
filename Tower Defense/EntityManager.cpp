#include "EntityManager.hpp"
#include "Entity.hpp"

EntityManager::EntityManager()
	: pool(100)
	, entities()
	, components()
{
}

Entity &EntityManager::createEntity()
{
	entities.emplace_back(*this, pool.createID());
	return entities.back();
}

void EntityManager::removeEntity(Entity entity)
{
	entities.erase(std::remove_if(
		entities.begin(),
		entities.end(),
		[&](const auto &e) { return e.getID() == entity.getID(); }),
		entities.end());

	components.erase(entity.getID());
	pool.removeID(entity.getID());
	
	// TODO
	//remove components
}

void EntityManager::addComponent(Entity &entity, Components::ID component)
{
	const unsigned int id = entity.getID();

	auto found = factories.find(component);
	assert(found != factories.end());

	components[id].insert(std::make_pair(component, found->second()));
}

void EntityManager::removeComponent(Entity &entity, Components::ID component)
{
	const unsigned int id = entity.getID();

	auto foundEntity = components.find(id);
	assert(foundEntity != components.end());

	auto foundComponent = components[id].find(component);
	assert(foundComponent != components[id].end());

	components[id].erase(component);
}

Component *EntityManager::getComponent(Entity &entity, Components::ID component)
{
	const unsigned int id = entity.getID();

	auto found = components.find(id);
	assert(found != components.end());

	auto it = components[id].find(component);
	if(it == components[id].end())
		return nullptr;

	return components[id][component].get();
}
