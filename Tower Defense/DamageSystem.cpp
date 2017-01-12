#include "DamageSystem.hpp"
#include "Entity.hpp"
#include "ComponentsData.hpp"
#include "EntityManager.hpp"	
#include "Gold.hpp"

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
		if (!target->target)
		{
			manager->requestEntityRemoval(entity->getID());
			continue;
		}

		auto targetPos = static_cast<PositionComponent*>(target->target->getComponent(Components::ID::PositionComponent));

		//if (position->x == targetPos->x && position->y == targetPos->y)
		if(isCollision(entity, target->target))
		{
			manager->requestEntityRemoval(entity->getID());
			
			auto hp = static_cast<HealthComponent*>(target->target->getComponent(Components::ID::HealthComponent));
			hp->health -= dmg->damage;
			hp->healthBar.setScale(static_cast<float>(hp->health) / 100, 1);

			if (hp->health <= 0)
			{
				manager->getContext().gold->addGold(4);
				manager->requestEntityRemoval(target->target->getID());
			}
		}
	}
}

bool DamageSystem::isCollision(Entity *projectile, Entity *target)
{
	auto targetRender = static_cast<RenderComponent*>(target->getComponent(Components::ID::RenderComponent));
	auto projRender = static_cast<RenderComponent*>(projectile->getComponent(Components::ID::RenderComponent));

	return targetRender->sprite.getGlobalBounds().intersects(projRender->sprite.getGlobalBounds());
}
