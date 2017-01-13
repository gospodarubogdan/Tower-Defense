#pragma once

#include "Widget.hpp"
#include "Label.hpp"
#include "Button.hpp"
#include "Gui.hpp"
#include "TowerTypes.hpp"
#include "GameContext.hpp"

namespace gui
{
	class HUD final : public Widget
	{
	public:
		enum class Action
		{
			None,
			Upgrade,
			Sell
		};

		HUD(States::Context context, World::GameData &gameData);

		void init();

		void handleEvent(const sf::Event &event) override;
		void update(sf::Time dt) override;

		void resetTowerType();
		Tower::Type getTowerType(const sf::Vector2i &mousePos);

		void setAction(Action action);
		const Action getAction() const;
	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		Action action;

		Gui container;
		States::Context context;
		World::GameData *gameData;

		sf::Texture texture;
		sf::Font font;

		Tower::Type turret;
		sf::Text totalGold;
		sf::Text totalLives;
		sf::Text currentLevel;

		Label singleTurret;
		Label splashTurret;
		Label frostTurret;

		sf::RectangleShape background;
	};
}
