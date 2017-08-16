#pragma once

#include <vector>

class EntityPool
{
public:
	explicit EntityPool(std::size_t size);
	~EntityPool();

	std::size_t createID();

	void removeID(std::size_t id);
	void resize(std::size_t size);
	void clear();

	std::size_t getSize() const;

private:
	size_t size;
	size_t nextID;

	std::vector<size_t> freeEntities;
	std::vector<size_t> entities;
};

