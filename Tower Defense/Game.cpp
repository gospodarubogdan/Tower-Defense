#include "Game.hpp"
#include "GameState.hpp"
#include <iostream>

Game::Game()
	: window({ 800, 600 }, "TD", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings{0,0, 8, 1, 1, 0, false})
	, context(window)
	, manager(context)
	, camera(context)
{
	//sf::Style::Titlebar | sf::Style::Close
	//window.create({ 1440, 900 }, "TD", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);
	registerStates();

	std::cout << window.getSize().x << ' ' << window.getSize().y << std::endl;

	manager.pushState(States::ID::Game);
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
}
