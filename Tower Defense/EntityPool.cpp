#include "EntityPool.hpp"
#include <assert.h>

EntityPool::EntityPool(std::size_t size)
	: size(size)
	, nextID(0)
	, freeEntities()
	, entities(size)
{
}

EntityPool::~EntityPool()
{
}

std::size_t EntityPool::createID()
{
	std::size_t id = 0;

	if (!freeEntities.empty())
	{
		id = freeEntities.back();
		freeEntities.pop_back();
	}
	else
	{
		id = nextID++;
		entities[id] = 1;
	}

	return id;
}

void EntityPool::removeID(std::size_t id)
{
	assert(id < entities.size());
	assert(entities[id] != 0);

	entities[id] = 0;
	freeEntities.push_back(id);
}

void EntityPool::resize(std::size_t size)
{
	entities.resize(size);
}

void EntityPool::clear()
{
	nextID = 0;
	entities.clear();
	freeEntities.clear();

	entities.resize(size);
}

const std::size_t EntityPool::getSize() const
{
	return entities.size();
}
