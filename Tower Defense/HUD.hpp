#pragma once

#include "Widget.hpp"
#include "Label.hpp"
#include "Button.hpp"

namespace gui
{
	class HUD final : public Widget
	{
	public:
		HUD();

		void handleEvent(const sf::Event &event) override;
		void update(sf::Time dt) override;

	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		sf::Texture texture;
		sf::Font font;

		sf::View hudView;
		Label turretInfo;
		Label selectedTurret;


	};
}
