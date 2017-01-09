#pragma once

class EntityManager;

class System
{
public:
	System() = default;
	virtual ~System() = default;

private:
	EntityManager *manager;
};