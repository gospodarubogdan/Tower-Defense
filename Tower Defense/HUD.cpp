#include "HUD.hpp"
#include "Gold.hpp"
using namespace gui;

HUD::HUD(States::Context context)
	: context(context)
{
	//hudView.setSize(window.getSize().x, 600);
	hudView.setViewport({ 0.f, 0.8f, 1.f, 1.f });

	texture.loadFromFile("data/test.png");
	turretInfo.setTexture(texture);
	turretInfo.setPosition(0.f, 0.f);

	font.loadFromFile("data/font.ttf");

	selectedTurret.setFont(font);
	selectedTurret.setText("Gold: " + std::to_string(context.gold->getGold()));
	selectedTurret.setPosition(10.f, 200.f);
	
}

void HUD::handleEvent(const sf::Event &event)
{
}

void HUD::update(sf::Time dt)
{
	selectedTurret.setText("Gold: " + std::to_string(context.gold->getGold()));
}

const sf::View &gui::HUD::getView()
{
	return hudView;
}

Tower::Type gui::HUD::getTowerType(const sf::Vector2i &mousePos)
{

	return Tower::Type::SingleTarget;
}

void HUD::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	//target.setView(target.getDefaultView());

	target.draw(turretInfo);
	target.draw(selectedTurret);
}
