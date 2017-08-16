#pragma once

#include "ComponentsID.hpp"

#include <SFML/Graphics.hpp>

class EntityManager;
class Entity;
class TextureManager;

class System
{
public:
	System() = default;
	virtual ~System() = default;

	virtual void update(sf::Time dt) = 0;
	
	void addEntity(Entity &entity);
	void removeEntity(unsigned int id);
	
	void setManager(EntityManager *manager);
	void setTextureManager(TextureManager *textureManager);
	Components::ID getSystemBits() const;

protected:
	EntityManager *manager;
	TextureManager *textureManager;
	Components::ID bitset;

	std::vector<Entity*> entities;
};