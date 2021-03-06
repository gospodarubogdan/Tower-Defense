#pragma once

#include "Component.hpp"
#include "Entity.hpp"
#include "EntityPool.hpp"
#include "System.hpp"
#include "../GameContext.hpp"

#include "../TextureManager.hpp"

#include <vector>
#include <unordered_map>
#include <map>
#include <functional>

class DrawSystem;

class EntityManager
{
public:
	friend class Entity;

	using EntityID = unsigned int;

	EntityManager(States::Context context, World::GameData &gameData);
	~EntityManager() = default;

	void update(sf::Time dt);
	void draw(sf::RenderWindow &window) const;

	template <typename T>
	void registerComponent(Components::ID component);

	void setSelectedEntity(Entity *entity);
	Entity *getSelectedEntity() const;

	void setLevelData(World::LevelData &levelData);
	World::LevelData &getLevelData() const;
	World::GameData &getGameData() const;

	Entity &createEntity();

	Entity *getEntity(const sf::Vector2i &mousePos) const;
	std::vector<Entity*> getEntities(Components::ID component);
	States::Context getContext() const;

	void requestEntityRemoval(EntityID entity);
	//void deleteEntities();

	void applyChanges();
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

	void addComponent(Entity &entity, Components::ID component);
	void removeComponent(Entity &entity, Components::ID component);
	Component *getComponent(Entity &entity, Components::ID component);

	World::GameData *gameData;
	World::LevelData *levelData;
	States::Context context;
	EntityPool pool;

	Entity *selectedEntity;
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
