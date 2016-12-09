#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "GameContext.hpp"

namespace gui
{
	class Widget : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
	{
	public:
		using Ptr = std::shared_ptr<Widget>;

		Widget() = default;
		virtual ~Widget() = default;

		virtual void handleEvent(const sf::Event &event) = 0;
		virtual void update(sf::Time dt) = 0;
	};
}
