#pragma once

#include "Component.hpp"
#include "Entity.hpp"
#include "EntityPool.hpp"

#include "ComponentsData.hpp"

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
