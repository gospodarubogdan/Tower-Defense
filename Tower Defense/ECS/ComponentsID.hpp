#pragma once

namespace Components
{
	enum ID
	{
		PositionComponent   = 1 << 0,
		VelocityComponent   = 1 << 1,
		HealthComponent     = 1 << 2,
		RangeComponent      = 1 << 3,
		ShootComponent      = 1 << 4,
		TargetComponent     = 1 << 5,
		RenderComponent     = 1 << 6,
		AIComponent         = 1 << 7,
		DamageComponent     = 1 << 8,
		SelectableComponent = 1 << 9,
		DirectionComponent  = 1 << 10,
		AnimationComponent  = 1 << 11,
		SplashComponent     = 1 << 12,
		SlowComponent       = 1 << 13,
		GoldComponent       = 1 << 14,
		UpgradeComponent    = 1 << 15
	};
}

inline Components::ID &operator|=(Components::ID &a, Components::ID b) 
{
	return a = static_cast<Components::ID> (a | b);
}