#include "System.hpp"
#include "Entity.hpp"
#include <algorithm>

void System::addEntity(Entity &entity)
{
	entities.push_back(&entity);
}

void System::removeEntity(unsigned int id)
{
	entities.erase(std::remove_if(
		entities.begin(),
		entities.end(),
		[&](const auto &e) { return e->getID() == id; }),
		entities.end());
}

void System::setManager(EntityManager *manager)
{
	this->manager = manager;
}

void System::setTextureManager(TextureManager *textureManager)
{
	this->textureManager = textureManager;
}

Components::ID System::getSystemBits() const
{
	return bitset;
}
