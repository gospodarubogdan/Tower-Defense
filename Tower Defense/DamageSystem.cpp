#include "DamageSystem.hpp"
#include "Entity.hpp"
#include "ComponentsData.hpp"
#include "EntityManager.hpp"	

DamageSystem::DamageSystem()
{
	bitset |= Components::ID::PositionComponent;
	bitset |= Components::ID::DamageComponent;
	bitset |= Components::ID::TargetComponent;
}

void DamageSystem::update(sf::Time dt)
{
	for (auto &entity : entities)
	{
		auto position = static_cast<PositionComponent*>(entity->getComponent(Components::ID::PositionComponent));
		auto dmg      = static_cast<DamageComponent*>(entity->getComponent(Components::ID::DamageComponent));
		auto target   = static_cast<TargetComponent*>(entity->getComponent(Components::ID::TargetComponent));

		// Target's position
		auto targetPos = static_cast<PositionComponent*>(target->target->getComponent(Components::ID::PositionComponent));

		if (position->x == targetPos->x && position->y == targetPos->y)
		{
			manager->requestEntityRemoval(entity->getID());
			
			auto hp = static_cast<TargetableComponent*>(target->target->getComponent(Components::ID::TargetableComponent));
			hp->health -= dmg->damage;

			if (hp->health <= 0)
			{
				manager->requestEntityRemoval(target->target->getID());
				auto turret = static_cast<TargetComponent*>(hp->parent->getComponent(Components::ID::TargetComponent));
				// make the entity pointer to nullptr inside entitymanager when removing the entity
				turret->target = nullptr;
			}
		}
	}
}
