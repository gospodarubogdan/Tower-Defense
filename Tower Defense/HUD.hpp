#pragma once

#include "Widget.hpp"
#include "Label.hpp"
#include "Button.hpp"
#include "TowerTypes.hpp"
#include "GameContext.hpp"

namespace gui
{
	class HUD final : public Widget
	{
	public:
		HUD(States::Context context);

		void handleEvent(const sf::Event &event) override;
		void update(sf::Time dt) override;

		const sf::View &getView();
		Tower::Type getTowerType(const sf::Vector2i &mousePos);
	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		States::Context context;

		sf::Texture texture;
		sf::Font font;

		sf::View hudView;
		Label turretInfo;
		Label selectedTurret;


	};
}
