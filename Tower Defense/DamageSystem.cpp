#include "DamageSystem.hpp"
#include "Entity.hpp"
#include "ComponentsData.hpp"
#include "EntityManager.hpp"	
#include "Gold.hpp"

#include <math.h>

DamageSystem::DamageSystem()
{
	bitset |= Components::ID::PositionComponent;
	bitset |= Components::ID::DamageComponent;
	bitset |= Components::ID::TargetComponent;
	//bitset |= Components::ID::HealthComponent;
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

void DamageSystem::addEntity(Entity &entity)
{
	if (entity.hasComponent(Components::ID::HealthComponent))
		enemies.push_back(&entity);
	else 
		entities.push_back(&entity);
}

void DamageSystem::removeEntity(unsigned int id)
{
	System::removeEntity(id);

	enemies.erase(std::remove_if(
		enemies.begin(),
		enemies.end(),
		[&](const auto &e) { return e->getID() == id; }),
		enemies.end());
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

	if (projectile->hasComponent(Components::ID::SlowComponent))
	{
		auto enemies = manager->getEntities(Components::ID::HealthComponent);

		for (auto &enemy : enemies)
		{
			auto enemyPos = static_cast<PositionComponent*>(enemy->getComponent(Components::ID::PositionComponent));

			if (getDistance(position, enemyPos) <= range->range)
			{
				auto slow = static_cast<SlowComponent*>(projectile->getComponent(Components::ID::SlowComponent));
				auto vel = static_cast<VelocityComponent*>(enemy->getComponent(Components::ID::VelocityComponent));
				vel->speed = slow->speed;
				vel->duration = sf::Time::Zero;
			}
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
				float scale = static_cast<float>(hp->health) / 2500.f;
				hp->healthBar.setSize({ 32.f * scale, 10 });

				if (hp->health <= 0)
				{
					manager->getContext().gold->addGold(4);
					manager->requestEntityRemoval(enemy->getID());
				}
			}
		}
	}

	auto target = static_cast<TargetComponent*>(projectile->getComponent(Components::ID::TargetComponent));
	auto hp = static_cast<HealthComponent*>(target->target->getComponent(Components::ID::HealthComponent));
	hp->health -= dmg->damage;
	float scale = static_cast<float>(hp->health) / 2500.f;
	hp->healthBar.setSize({ 32.f * scale, 10 });

	if (hp->health <= 0)
	{
		manager->getContext().gold->addGold(4);
		manager->requestEntityRemoval(target->target->getID());
	}
}

int DamageSystem::getDistance(PositionComponent *posOne, PositionComponent *posTwo)
{
	int x = posOne->x - posTwo->x;
	int y = posOne->y - posTwo->y;
	return abs(sqrt(x * x + y * y));
}
