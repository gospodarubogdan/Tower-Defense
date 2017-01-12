#include "AnimationSystem.hpp"
#include "ComponentsData.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"

AnimationSystem::AnimationSystem()
{
	bitset |= Components::ID::DirectionComponent;
	bitset |= Components::ID::AnimationComponent;
	bitset |= Components::ID::RenderComponent;
}

void AnimationSystem::update(sf::Time dt)
{
	for (auto &entity : entities)
	{
		auto direction = static_cast<DirectionComponent*>(entity->getComponent(Components::ID::DirectionComponent));
		auto renderer  = static_cast<RenderComponent*>(entity->getComponent(Components::ID::RenderComponent));
		auto anim      = static_cast<AnimationComponent*>(entity->getComponent(Components::ID::AnimationComponent));

		if (direction->changed)
		{
			direction->changed = false;
			anim->frame = 0;
			updateTexture(direction->dir, anim->frame, renderer->sprite);
			continue;
		}

		anim->elapsedTime += dt;
		if (anim->elapsedTime.asSeconds() >= 0.2f)
		{
			updateTexture(direction->dir, anim->frame, renderer->sprite);
			anim->elapsedTime = sf::Time::Zero;
		}
	}
}

void AnimationSystem::updateTexture(Direction direction, int &frame, sf::Sprite &sprite)
{
	if (frame > 2)
		frame = 0;

	switch (direction)
	{
	case Direction::Up:
		sprite.setTextureRect({ frame * 32, 96, 32, 32});
		break;
	case Direction::Down:
		sprite.setTextureRect({ frame * 32, 0, 32, 32 });
		break;
	case Direction::Right:
		sprite.setTextureRect({ frame * 32, 64, 32, 32 });
		break;
	case Direction::Left:
		sprite.setTextureRect({ frame * 32, 32, 32, 32 });
		break;
	}

	frame++;
}
