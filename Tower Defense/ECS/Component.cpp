#include "Component.hpp"

Component::Component(Entity *parent)
{
	setParent(parent);
}

void Component::setParent(Entity *parent)
{
	this->parent = parent;
}

Entity *Component::getParent() const
{
	return parent;
}
