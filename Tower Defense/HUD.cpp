#include "HUD.hpp"
#include "TextureManager.hpp"

using namespace gui;

HUD::HUD(States::Context context, World::GameData &gameData)
	: context(context)
	, gameData(&gameData)
{
	background.setFillColor(sf::Color(169, 169, 169));
	background.setPosition(0.f, 480.f);
	background.setSize({ 800, 120 });

	auto upgrade = std::make_shared<gui::Button>(*context.soundManager);// (*getContext().soundPlayer);
	upgrade->setTexture(context.textureManager->getTexture("buttonGreen"));
	upgrade->setPosition({ 600.f, 485.f });
	upgrade->setFont(*context.font);
	upgrade->setText("Upgrade");
	upgrade->setCallback([this]()
	{
		this->context.cursor->setTexture(this->context.textureManager->getTexture("cursorUpgrade"));
		action = Action::Upgrade;
	});

	auto sell = std::make_shared<gui::Button>(*context.soundManager);// (*getContext().soundPlayer);
	sell->setTexture(context.textureManager->getTexture("buttonGreen"));
	sell->setPosition({ 600.f, 550.f });
	sell->setFont(*context.font);
	sell->setText("Sell");
	sell->setCallback([this]()
	{
		this->context.cursor->setTexture(this->context.textureManager->getTexture("cursorSell"));
		action = Action::Sell;
	});
	container.addWidget(upgrade);
	container.addWidget(sell);

	action = Action::None;
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
	totalLives.setPosition(0.f, 540.f);

	currentLevel.setFont(*context.font);
	currentLevel.setString("Level: " + std::to_string(gameData->currentLevel));
	currentLevel.setPosition(0.f, 580.f);
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
	else if (event.type == sf::Event::MouseButtonPressed
		&& event.key.code == sf::Mouse::Right)
	{
		action = Action::None;
	}

	container.handleWidgetsEvent(event);
}

void HUD::update(sf::Time dt)
{
	totalGold.setString("Gold: " + std::to_string(gameData->gold));
	totalLives.setString("Lives: " + std::to_string(gameData->lives));
	currentLevel.setString("Level: " + std::to_string(gameData->currentLevel + 1));

	container.updateWidgets(dt);
}

void gui::HUD::resetTowerType()
{
	turret = Tower::Type::None;
}

Tower::Type gui::HUD::getTowerType(const sf::Vector2i &mousePos)
{
	return turret;
}

void gui::HUD::setAction(Action action)
{
	this->action = action;
}

const HUD::Action HUD::getAction() const
{
	return action;
}

void HUD::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(background);
	target.draw(singleTurret);
	target.draw(splashTurret);
	target.draw(frostTurret);
	target.draw(totalGold);
	target.draw(totalLives);
	target.draw(currentLevel);
	target.draw(container);
}
