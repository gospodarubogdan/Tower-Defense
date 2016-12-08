#include "Game.hpp"

Game::Game()
	: context(window)
	, manager(context)
{
	window.create({ 800, 600 }, "TD", sf::Style::Titlebar | sf::Style::Close);

	registerStates();
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

	manager.draw();

	window.display();
}

void Game::registerStates()
{
}
