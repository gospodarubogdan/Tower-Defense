#include "Game.hpp"
#include "GameState.hpp"
#include "MenuState.hpp"

Game::Game()
	: window({ 800, 600 }, "TD", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings{0,0, 8, 1, 1, 0, false})
	, context(window, font, textureManager, gold)
	, manager(context)
	, camera(context)
{
	//sf::Style::Titlebar | sf::Style::Close
	//window.create({ 1440, 900 }, "TD", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);

	font.loadFromFile("data/font.ttf");

	textureManager.loadFromFile("buttonGreen", "data/button_green.png");
	textureManager.loadFromFile("buttonRed", "data/button_red.png");
	textureManager.loadFromFile("panel", "data/panel.png");

	registerStates();
	manager.pushState(States::ID::Menu);
}

void Game::run()
{
	const sf::Time frameTime = sf::seconds(1.f / 60.f);
	sf::Clock clock;
	sf::Time passedTime = sf::Time::Zero;

	while (window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		passedTime += elapsedTime;

		// Physics, logics etc
		while (passedTime > frameTime)
		{
			passedTime -= frameTime;
			
			processEvents();
			update(frameTime);

			if (manager.isEmpty())
				window.close();
		}

		// Rendering
		draw();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		manager.processEvents(event);
	}
}

void Game::update(sf::Time frameTime)
{
	manager.update(frameTime);
}

void Game::draw()
{
	window.clear();

	//camera.draw();
	manager.draw();

	window.display();
}

void Game::registerStates()
{
	manager.registerState<GameState>(States::ID::Game);
	manager.registerState<MenuState>(States::ID::Menu);
}
