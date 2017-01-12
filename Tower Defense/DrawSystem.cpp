#include "DrawSystem.hpp"
#include "Entity.hpp"
#include "ComponentsData.hpp"

DrawSystem::DrawSystem()
{
	bitset |= Components::ID::PositionComponent;
	bitset |= Components::ID::RenderComponent;
}

void DrawSystem::update(sf::Time dt)
{
}

void DrawSystem::draw(sf::RenderWindow &window)
{
	for (auto &entity : entities)
	{
		auto position = static_cast<PositionComponent*>(entity->getComponent(Components::ID::PositionComponent));
		auto render   = static_cast<RenderComponent*>(entity->getComponent(Components::ID::RenderComponent));

		render->sprite.setPosition(position->x, position->y);
		
		window.draw(render->sprite);
		if (entity->hasComponent(Components::ID::RangeComponent))
		{
			auto circle = static_cast<RangeComponent*>(entity->getComponent(Components::ID::RangeComponent));
			window.draw(circle->range);
		}

		if (entity->hasComponent(Components::ID::HealthComponent))
		{
			auto bar = static_cast<HealthComponent*>(entity->getComponent(Components::ID::HealthComponent));
			window.draw(bar->healthBar);
		}
	}
}

