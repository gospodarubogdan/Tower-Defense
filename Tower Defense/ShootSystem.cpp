#include "ShootSystem.hpp"
#include "Entity.hpp"
#include "ComponentsData.hpp"
#include "EntityManager.hpp"

ShootSystem::ShootSystem()
{
	bitset |= Components::ID::PositionComponent;
	bitset |= Components::ID::ShootComponent;
	bitset |= Components::ID::RangeComponent;
	bitset |= Components::ID::TargetComponent;
}

void ShootSystem::update(sf::Time dt)
{
	for (auto &entity : entities)
	{
		auto position = static_cast<PositionComponent*>(entity->getComponent(Components::ID::PositionComponent));
		auto range    = static_cast<RangeComponent*>(entity->getComponent(Components::ID::RangeComponent));
		auto target   = static_cast<TargetComponent*>(entity->getComponent(Components::ID::TargetComponent));
		auto shoot    = static_cast<ShootComponent*>(entity->getComponent(Components::ID::ShootComponent));

			
		if (target->target && !isTargetInRange(range->range, target->target))
			target->target = nullptr;

		if (!target->target)
			selectTarget(range->range, target->target);

		shoot->elapsedTime += dt;
		if (shoot->elapsedTime.asSeconds() >= shoot->attackSpeed)
		{
			shoot->elapsedTime = sf::Time::Zero;

			if (target->target != nullptr)
			{
				createProjectile(position->x, position->y, target->target);
			}
		}
	}
}

void ShootSystem::selectTarget(const sf::CircleShape &range, Entity *&target)
{
	auto &entities = manager->getEntities(Components::ID::HealthComponent);

	for (const auto &e : entities)
	{
		auto render = static_cast<RenderComponent*>(e->getComponent(Components::ID::RenderComponent));

		if (render->sprite.getGlobalBounds().intersects(range.getGlobalBounds()))
		{
			target = e;
			break;
		}
	}
}

void ShootSystem::createProjectile(int x, int y, Entity *target)
{
	auto &entity = manager->createEntity();
	entity.addComponent(Components::ID::PositionComponent);
	entity.addComponent(Components::ID::VelocityComponent);
	entity.addComponent(Components::ID::RenderComponent);
	entity.addComponent(Components::ID::DamageComponent);
	entity.addComponent(Components::ID::TargetComponent);

	std::cout << "Bullet created...\n";

	auto pos = static_cast<PositionComponent*>(entity.getComponent(Components::ID::PositionComponent));
	pos->x = x;
	pos->y = y;

	auto vel = static_cast<VelocityComponent*>(entity.getComponent(Components::ID::VelocityComponent));
	vel->speed = 250.f;

	auto dmg = static_cast<DamageComponent*>(entity.getComponent(Components::ID::DamageComponent));
	dmg->damage = 60;

	auto render = static_cast<RenderComponent*>(entity.getComponent(Components::ID::RenderComponent));
	render->sprite.setTexture(manager->getContext().textureManager->getTexture("bullet"));

	auto targetComp = static_cast<TargetComponent*>(entity.getComponent(Components::ID::TargetComponent));
	
	targetComp->target = target;
}

bool ShootSystem::isTargetInRange(const sf::CircleShape &range, Entity *target)
{
	//std::cout << "is in range\n";
	auto render = static_cast<RenderComponent*>(target->getComponent(Components::ID::RenderComponent));
	return render->sprite.getGlobalBounds().intersects(range.getGlobalBounds());
}
