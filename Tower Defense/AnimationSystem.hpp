#pragma once

#include "System.hpp"

enum class Direction;

class AnimationSystem : public System
{
public:
	AnimationSystem();
	~AnimationSystem() = default;

	void update(sf::Time dt) override;

private:
	void updateTexture(Direction direction, int &frame, sf::Sprite &sprite);
};
