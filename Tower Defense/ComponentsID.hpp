#pragma once

const unsigned int MAX_COMPONENTS = 32;

namespace Components
{
	enum class ID
	{
		None = 0,
		PositionComponent,
		VelocityComponent,
		RenderComponent
	};
}