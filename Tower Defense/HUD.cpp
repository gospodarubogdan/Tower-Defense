#include "HUD.hpp"

using namespace gui;

HUD::HUD(sf::RenderWindow &window)
	: window(window)
{
	//hudView.setSize(window.getSize().x, 600);
	hudView.setViewport({ 0.f, 0.8f, 1.f, 1.f });

	texture.loadFromFile("data/test.png");
	turretInfo.setTexture(texture);
	turretInfo.setPosition(0.f, 0.f);

	font.loadFromFile("data/font.ttf");

	selectedTurret.setFont(font);
	selectedTurret.setText("Turret selected");
	selectedTurret.setPosition(10.f, 200.f);
	
}

void HUD::handleEvent(const sf::Event &event)
{
}

void HUD::update(sf::Time dt)
{
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
