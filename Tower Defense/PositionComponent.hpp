#pragma once

#include "Component.hpp"

class PositionComponent : public Component
{
public:
	PositionComponent() = default;
	~PositionComponent() = default;

	int x, y;
};