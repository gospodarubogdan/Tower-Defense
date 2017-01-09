#pragma once

namespace Components
{
	enum ID : char
	{
		PositionComponent = 1 << 0,
		VelocityComponent = 1 << 1,
		HealthComponent   = 1 << 2,
		RangeComponent    = 1 << 3
	};
}

inline Components::ID &operator|=(Components::ID &a, Components::ID b) 
{
	return a = static_cast<Components::ID> (a | b);
}