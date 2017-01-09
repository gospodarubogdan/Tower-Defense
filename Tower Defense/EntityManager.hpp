#pragma once

#include "Component.hpp"
#include "Entity.hpp"
#include "EntityPool.hpp"

#include "PositionComponent.hpp"

#include <assert.h>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <iostream>
#include <functional>

class EntityManager
{
public:
	friend class Entity;

	using EntityID = unsigned int;

	EntityManager();
	~EntityManager() = default;

	template <typename T>
	void registerState(Components::ID component);

	Entity &createEntity();

	void removeEntity(Entity entity);
	//void deleteEntities();

private:
	template <typename T>
	void addComponent(Entity &entity);

	template <typename T>
	void removeComponent(Entity &entity);

	template <typename T>
	T &getComponent(Entity &entity);

	void addComponent(Entity &entity, Components::ID component);
	void removeComponent(Entity &entity, Components::ID component);
	Component *getComponent(Entity &entity, Components::ID component);

	EntityPool pool;

	std::vector<Entity> entities;
	//std::vector<PositionComponent> posComponents;
	std::map<Components::ID, std::function<Component::Ptr()>> factories;
	std::unordered_map<EntityID, std::unordered_map<Components::ID, Component::Ptr>> components;
};

template <typename T>
void EntityManager::registerState(Components::ID component)
{
	factories[component] = [this]()
	{
		return Component::Ptr(std::make_unique<T>());
	}
}

template <typename T>
void EntityManager::addComponent(Entity &entity)
{
	static_assert(std::is_base_of<Component, T>::value, "Class T is not a component.");

	const unsigned int id = entity.getID();
	//if()
	//if entity bitset !contains component do
	//if(entity.hasComponent(T.name()))
	components[id].insert(std::make_unique<T>());
}

template<typename T>
void EntityManager::removeComponent(Entity &entity)
{
	static_assert(std::is_base_of<Component, T>::value, "Class T is not a component.");

	const unsigned int id = entity.getID();

	auto found = components.find(id);
	assert(found != components.end());

	components[id].erase(std::remove_if(
		components[id].begin(),
		components[id].end(),
		[](const auto &c) { return typeid(*c).name() == typeid(T).name(); }),
		components[id].end());
}

template<typename T>
T &EntityManager::getComponent(Entity &entity)
{
	static_assert(std::is_base_of<Component, T>::value, "Class T is not a component.");

	const unsigned int id = entity.getID();

	auto found = components.find(id);
	assert(found != components.end());

	//auto it = components[id][]

	/*auto it = std::find_if(
		components[id].begin(),
		components[id].end(),
		[](const auto &c) { return typeid(*c).name() == typeid(T).name(); });

	assert(it != components[id].end());*/

	return static_cast<T&>(*it->get());
}