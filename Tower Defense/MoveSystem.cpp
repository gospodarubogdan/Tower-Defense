#include "MoveSystem.hpp"
#include "Entity.hpp"

MoveSystem::MoveSystem()
{

}

void MoveSystem::update(sf::Time dt)
{
}

void MoveSystem::addComponent(Entity &entity, Components::ID component)
{
	switch (component)
	{
	case Components::ID::PositionComponent:
		posComponents.push_back(static_cast<PositionComponent*>(entity.getComponent(component)));
		break;
	case Components::ID::VelocityComponent:
		velComponents.push_back(static_cast<VelocityComponent*>(entity.getComponent(component)));
		break;
	}
}
