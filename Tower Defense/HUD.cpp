#include "HUD.hpp"

using namespace gui;

HUD::HUD()
{
	texture.loadFromFile("data/test.png");
	turretInfo.setTexture(texture);
	turretInfo.setPosition(15.f, 15.f);

	font.loadFromFile("data/font.ttf");

	selectedTurret.setFont(font);
	selectedTurret.setText("Turret selected");
	selectedTurret.setPosition(200.f, 15.f);
}

void HUD::handleEvent(const sf::Event &event)
{
}

void HUD::update(sf::Time dt)
{
}

void HUD::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	//target.setView(target.getDefaultView());

	target.draw(turretInfo);
	target.draw(selectedTurret);
}
