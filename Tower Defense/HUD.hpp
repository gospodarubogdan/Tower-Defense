#pragma once

#include "Widget.hpp"
#include "Label.hpp"
#include "Button.hpp"
#include "TowerTypes.hpp"

namespace gui
{
	class HUD final : public Widget
	{
	public:
		HUD(sf::RenderWindow &window);

		void handleEvent(const sf::Event &event) override;
		void update(sf::Time dt) override;

		const sf::View &getView();
		Tower::Type getTowerType(const sf::Vector2i &mousePos);
	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		sf::RenderWindow &window;

		sf::Texture texture;
		sf::Font font;

		sf::View hudView;
		Label turretInfo;
		Label selectedTurret;


	};
}
