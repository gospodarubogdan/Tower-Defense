#include "EntityManager.hpp"
#include "Entity.hpp"
#include "GameState.hpp"

#include "DrawSystem.hpp"
#include "ShootSystem.hpp"
#include "MoveSystem.hpp"
#include "AISystem.hpp"
#include "DamageSystem.hpp"
#include "AnimationSystem.hpp"

EntityManager::EntityManager(States::Context context, World::GameData &gameData)
	: context(context)
	, gameData(&gameData)
	, pool(300)
	, entities()
	, components()
{
	registerComponents();
	initializeSystems();
}

void EntityManager::update(sf::Time dt)
{
	for (auto &system : systems)
		system->update(dt);

	applyChanges();
}

void EntityManager::draw(sf::RenderWindow &window)
{
	renderer->draw(window);
}

void EntityManager::setSelectedEntity(Entity *entity)
{
	selectedEntity = entity;
}

Entity *EntityManager::getSelectedEntity() const
{
	return selectedEntity;
}

void EntityManager::setLevelData(World::LevelData &levelData)
{
	this->levelData = &levelData;
}

World::LevelData &EntityManager::getLevelData()
{
	return *levelData;
}

World::GameData &EntityManager::getGameData()
{
	return *gameData;
}

Entity &EntityManager::createEntity()
{
	int id = pool.createID();
	auto temp = std::make_unique<Entity>(*this, id);

	actionQueue.push_back(std::make_pair(Action::Add, id));
	entities.insert(std::make_pair(id, std::move(temp)));

	return *entities[id].get();
}

Entity *EntityManager::getEntity(const sf::Vector2i &mousePos) const
{
	for (const auto &entity : entities)
		if (entity.second->hasComponent(Components::ID::SelectableComponent))
		{
			auto bounding = static_cast<SelectableComponent*>(entity.second->getComponent(Components::ID::SelectableComponent));
			if (bounding->box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
				return entity.second.get();
		}

	return nullptr;
}

std::vector<Entity*> EntityManager::getEntities(Components::ID component)
{
	std::vector<Entity*> temp;
	for (const auto &entity : entities)
		if (entity.second->hasComponent(component))
			temp.push_back(entity.second.get());

	return temp;
}

States::Context EntityManager::getContext() const
{
	return context;
}

void EntityManager::requestEntityRemoval(EntityID entity)
{
	actionQueue.push_back(std::make_pair(Action::Remove, entity));
}

void EntityManager::registerComponents()
{
	registerComponent<PositionComponent>(Components::ID::PositionComponent);
	registerComponent<VelocityComponent>(Components::ID::VelocityComponent);
	registerComponent<RenderComponent>(Components::ID::RenderComponent);
	registerComponent<RangeComponent>(Components::ID::RangeComponent);
	registerComponent<HealthComponent>(Components::ID::HealthComponent);
	registerComponent<ShootComponent>(Components::ID::ShootComponent);
	registerComponent<TargetComponent>(Components::ID::TargetComponent);
	registerComponent<AIComponent>(Components::ID::AIComponent);
	registerComponent<DamageComponent>(Components::ID::DamageComponent);
	registerComponent<SelectableComponent>(Components::ID::SelectableComponent);
	registerComponent<DirectionComponent>(Components::ID::DirectionComponent);
	registerComponent<AnimationComponent>(Components::ID::AnimationComponent);
	registerComponent<SplashComponent>(Components::ID::SplashComponent);
	registerComponent<SlowComponent>(Components::ID::SlowComponent);
	registerComponent<GoldComponent>(Components::ID::GoldComponent);
	registerComponent<UpgradeComponent>(Components::ID::UpgradeComponent);
}

void EntityManager::initializeSystems()
{
	auto drawSystem  = std::make_unique<DrawSystem>();
	renderer = drawSystem.get();

	systems.push_back(std::move(drawSystem));
	systems.push_back(std::make_unique<ShootSystem>());
	systems.push_back(std::make_unique<MoveSystem>());
	systems.push_back(std::make_unique<AISystem>());
	systems.push_back(std::make_unique<DamageSystem>());
	systems.push_back(std::make_unique<AnimationSystem>());

	for (auto &system : systems)
	{
		system->setManager(this);
		system->setTextureManager(textureManager);
	}
}

void EntityManager::addToSystems(EntityID entity)
{
	for (auto &system : systems)
		if ((system->getSystemBits() & entities[entity]->getBits()) == system->getSystemBits())
			system->addEntity(*entities[entity].get());
}

void EntityManager::removeEntity(EntityID entity)
{
	auto found = entities.find(entity);
	if (found == entities.end()) return;

	int temp = entities[entity]->getBits();

	for(auto &e : entities)
		if (e.second->hasComponent(Components::ID::TargetComponent))
		{
			auto target = static_cast<TargetComponent*>(e.second->getComponent(Components::ID::TargetComponent));
			if (target->target && target->target->getID() == entities[entity]->getID())
				target->target = nullptr;
		}

	for (auto &system : systems)
	{
		if (((system->getSystemBits() & temp) == system->getSystemBits()))
			system->removeEntity(entity);
	}
	entities[entity]->clearComponents();

	entities.erase(entity);
	pool.removeID(entity);
}

void EntityManager::applyChanges()
{
	for (const auto &change : actionQueue)
	{
		switch (change.first)
		{
		case Action::Add:
			addToSystems(change.second);
			break;
		case Action::Remove:
			removeEntity(change.second);
			break;
		default:
			break;
		}
	}

	actionQueue.clear();
}

void EntityManager::addComponent(Entity &entity, Components::ID component)
{
	const unsigned int id = entity.getID();

	auto found = factories.find(component);
	assert(found != factories.end());

	components[id].insert(std::make_pair(component, found->second()));
	/*auto temp = found->second();
	temp->setParent(&entity);
	components.push_back(std::move(temp));*/
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

	/*for (const auto &c : components)
	{
		if (c->getParent() == &entity)
			return c.get();
	}*/
}
