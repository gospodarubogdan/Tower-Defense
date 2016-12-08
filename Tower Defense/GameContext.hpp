#pragma once

namespace sf
{
	class RenderWindow;
}

namespace States
{
	class Context
	{
	public:
		explicit Context(sf::RenderWindow &window)
			: window(&window)
		{};

		sf::RenderWindow *window;
	};
}