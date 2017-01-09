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

	const std::size_t getSize() const;

private:
	std::size_t size;
	std::size_t nextID;

	std::vector<std::size_t> freeEntities;
	std::vector<std::size_t> entities;
};

