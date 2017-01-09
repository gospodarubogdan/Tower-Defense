#include "System.hpp"

void System::setManager(EntityManager *manager)
{
	this->manager = manager;
}

void System::setComponents(Components::ID components)
{
	bitset = components;
}
