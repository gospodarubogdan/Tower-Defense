#include "DamageSystem.hpp"
#include "Entity.hpp"
#include "ComponentsData.hpp"
#include "EntityManager.hpp"	

#include <math.h>

DamageSystem::DamageSystem()
{
	bitset |= Components::ID::PositionComponent;
	bitset |= Components::ID::VelocityComponent;
	bitset |= Components::ID::DamageComponent;
	bitset |= Components::ID::TargetComponent;
}

void DamageSystem::update(sf::Time dt)
{
	for (auto &entity : entities)
	{
		auto target   = static_cast<TargetComponent*>(entity->getComponent(Components::ID::TargetComponent));

		// Target's position
		if (!target->target)
		{
			manager->requestEntityRemoval(entity->getID());
			continue;
		}

		if(isCollision(entity, target->target))
		{
			manager->requestEntityRemoval(entity->getID());
			dealDamage(dt, entity);
		}
	}
}

bool DamageSystem::isCollision(Entity *projectile, Entity *target)
{
	auto targetRender = static_cast<RenderComponent*>(target->getComponent(Components::ID::RenderComponent));
	auto projRender = static_cast<RenderComponent*>(projectile->getComponent(Components::ID::RenderComponent));

	return targetRender->sprite.getGlobalBounds().intersects(projRender->sprite.getGlobalBounds());
}

void DamageSystem::dealDamage(sf::Time dt, Entity *projectile)
{
	auto dmg = static_cast<DamageComponent*>(projectile->getComponent(Components::ID::DamageComponent));
	auto range = static_cast<SplashComponent*>(projectile->getComponent(Components::ID::SplashComponent));
	auto position = static_cast<PositionComponent*>(projectile->getComponent(Components::ID::PositionComponent));

	int maxHP = manager->getLevelData().hp;
	int goldPerMinion = manager->getLevelData().goldPerMinion;

	if (projectile->hasComponent(Components::ID::SlowComponent)
		&& !manager->getLevelData().immuneToSlow)
	{
		auto enemies = manager->getEntities(Components::ID::HealthComponent);

		for (auto &enemy : enemies)
		{
			auto enemyPos = static_cast<PositionComponent*>(enemy->getComponent(Components::ID::PositionComponent));

			if (getDistance(position, enemyPos) <= range->range)
			{
				auto slow = static_cast<SlowComponent*>(projectile->getComponent(Components::ID::SlowComponent));
				auto vel = static_cast<VelocityComponent*>(enemy->getComponent(Components::ID::VelocityComponent));
				vel->speed = manager->getLevelData().movementSpeed * slow->speed;
				vel->duration = sf::Time::Zero;
			}

			auto hp = static_cast<HealthComponent*>(enemy->getComponent(Components::ID::HealthComponent));

			hp->health -= dmg->damage;

			if (hp->health <= 0)
			{
				hp->health = 0;
				manager->getGameData().gold += goldPerMinion;
				manager->requestEntityRemoval(enemy->getID());
			}

			float scale = static_cast<float>(hp->health) / static_cast<float>(maxHP);
			hp->healthBar.setSize({ 32.f * scale, 10 });
		}
	}
	else if (projectile->hasComponent(Components::ID::SplashComponent))
	{
		auto enemies = manager->getEntities(Components::ID::HealthComponent);

		for (auto &enemy : enemies)
		{
			auto enemyPos = static_cast<PositionComponent*>(enemy->getComponent(Components::ID::PositionComponent));

			if (getDistance(position, enemyPos) <= range->range)
			{
				auto hp = static_cast<HealthComponent*>(enemy->getComponent(Components::ID::HealthComponent));

				hp->health -= dmg->damage;

				if (hp->health <= 0)
				{
					hp->health = 0;
					manager->getGameData().gold += goldPerMinion;
					manager->requestEntityRemoval(enemy->getID());
				}

				float scale = static_cast<float>(hp->health) / static_cast<float>(maxHP);
				hp->healthBar.setSize({ 32.f * scale, 10 });
			}
		}
	}

	auto target = static_cast<TargetComponent*>(projectile->getComponent(Components::ID::TargetComponent));
	auto hp = static_cast<HealthComponent*>(target->target->getComponent(Components::ID::HealthComponent));
	hp->health -= dmg->damage;

	if (hp->health <= 0)
	{
		hp->health = 0;
		manager->getGameData().gold += goldPerMinion;
		manager->requestEntityRemoval(target->target->getID());
	}

	float scale = static_cast<float>(hp->health) / static_cast<float>(maxHP);
	hp->healthBar.setSize({ 32.f * scale, 10 });

}

int DamageSystem::getDistance(PositionComponent *posOne, PositionComponent *posTwo)
{
	int x = posOne->x - posTwo->x;
	int y = posOne->y - posTwo->y;
	return abs(sqrt(x * x + y * y));
}
