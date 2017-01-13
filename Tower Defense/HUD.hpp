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
		HUD(States::Context context, World::GameData &gameData);

		void init();

		void handleEvent(const sf::Event &event) override;
		void update(sf::Time dt) override;

		void resetTowerType();
		Tower::Type getTowerType(const sf::Vector2i &mousePos);
	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		States::Context context;
		World::GameData *gameData;

		sf::Texture texture;
		sf::Font font;

		Tower::Type turret;
		sf::Text totalGold;
		sf::Text totalLives;

		Label singleTurret;
		Label splashTurret;
		Label frostTurret;
		sf::RectangleShape background;
	};
}
