#include "HUD.hpp"
#include "TextureManager.hpp"

using namespace gui;

HUD::HUD(States::Context context, World::GameData &gameData)
	: context(context)
	, gameData(&gameData)
{
	
}

void HUD::init()
{
	singleTurret.setTexture(context.textureManager->getTexture("singleTarget"));
	singleTurret.setPosition(268.f, 500.f);

	splashTurret.setTexture(context.textureManager->getTexture("splash"));
	splashTurret.setPosition(368.f, 500.f);

	frostTurret.setTexture(context.textureManager->getTexture("frost"));
	frostTurret.setPosition(468.f, 500.f);

	totalGold.setFont(*context.font);
	totalGold.setString("Gold: " + std::to_string(gameData->gold));
	totalGold.setPosition(0.f, 500.f);
	
	totalLives.setFont(*context.font);
	totalLives.setString("Lives: " + std::to_string(gameData->lives));
	totalLives.setPosition(0.f, 560.f);

	background.setFillColor(sf::Color(169, 169, 169));
	background.setPosition(0.f, 480.f);
	background.setSize({ 800, 120 });
}

void HUD::handleEvent(const sf::Event &event)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*context.window);
	if (event.type == sf::Event::MouseButtonPressed
		&& event.key.code == sf::Mouse::Left)
	{
		if (singleTurret.isMouseOver(mousePos))
			turret = Tower::Type::SingleTarget;
		else if (splashTurret.isMouseOver(mousePos))
			turret = Tower::Type::Splash;
		else if (frostTurret.isMouseOver(mousePos))
			turret = Tower::Type::Frost;
	}
}

void HUD::update(sf::Time dt)
{
	totalGold.setString("Gold: " + std::to_string(gameData->gold));
	totalLives.setString("Lives: " + std::to_string(gameData->lives));
}

void gui::HUD::resetTowerType()
{
	turret = Tower::Type::None;
}

Tower::Type gui::HUD::getTowerType(const sf::Vector2i &mousePos)
{
	return turret;
}

void HUD::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.setView(target.getDefaultView());

	target.draw(background);
	target.draw(singleTurret);
	target.draw(splashTurret);
	target.draw(frostTurret);
	target.draw(totalGold);
	target.draw(totalLives);
}
