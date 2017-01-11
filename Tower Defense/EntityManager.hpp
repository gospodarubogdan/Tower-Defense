#pragma once

#include "Component.hpp"
#include "Entity.hpp"
#include "EntityPool.hpp"
#include "System.hpp"

#include "ComponentsData.hpp"

#include "TextureManager.hpp"

#include <assert.h>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <iostream>
#include <functional>

class DrawSystem;

class EntityManager
{
public:
	friend class Entity;

	using EntityID = unsigned int;

	EntityManager(TextureManager *textureManager);
	~EntityManager() = default;

	void update(sf::Time dt);
	void draw(sf::RenderWindow &window);

	template <typename T>
	void registerComponent(Components::ID component);

	Entity &createEntity();

	std::vector<Entity*> getEntities(Components::ID component);

	void requestEntityRemoval(EntityID entity);
	//void deleteEntities();

private:
	enum class Action
	{
		Add,
		Remove
	};
	std::vector<std::pair<Action, EntityID>> actionQueue;

	void registerComponents();
	void initializeSystems();

	void addToSystems(EntityID entity);
	void removeEntity(EntityID entity);
	void applyChanges();

	void addComponent(Entity &entity, Components::ID component);
	void removeComponent(Entity &entity, Components::ID component);
	Component *getComponent(Entity &entity, Components::ID component);

	EntityPool pool;

	TextureManager *textureManager;

	DrawSystem *renderer;
	std::vector<std::unique_ptr<System>> systems;
	std::unordered_map<EntityID, std::unique_ptr<Entity>> entities;
	//std::vector<PositionComponent> posComponents;
	std::map<Components::ID, std::function<Component::Ptr()>> factories;
	std::unordered_map<EntityID, std::unordered_map<Components::ID, Component::Ptr>> components;

	//std::vector<Component::Ptr> components;
};

template <typename T>
void EntityManager::registerComponent(Components::ID component)
{
	factories[component] = [this]()
	{
		return Component::Ptr(std::make_unique<T>());
	};
}
