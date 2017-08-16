#pragma once

#include <memory>

class Entity;

class Component
{
public:
	using Ptr = std::unique_ptr<Component>; //typedef std::unique_ptr<Component> Ptr;

	Component() = default;
	Component(Entity *parent);
	virtual ~Component() = default;

	void setParent(Entity *parent);
	Entity *getParent() const;

private:
	Entity *parent;
};