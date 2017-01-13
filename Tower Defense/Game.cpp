#include "Game.hpp"
#include "GameState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"

Game::Game()
	: window({ 800, 600 }, "TD", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings{0,0, 8, 1, 1, 0, false})
	, context(window, font, textureManager, soundManager, cursor, score)
	, manager(context)
	, camera(context)
{
	//sf::Style::Titlebar | sf::Style::Close
	//window.create({ 1440, 900 }, "TD", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);
	//window.setFramerateLimit(60);

	font.loadFromFile("data/font.ttf");
	score.setFont(font);

	textureManager.loadFromFile("buttonGreen", "data/button_green.png");
	textureManager.loadFromFile("buttonRed", "data/button_red.png");
	textureManager.loadFromFile("panel", "data/panel.png");
	textureManager.loadFromFile("cursorNormal", "data/cursor/normal_cursor.png");
	textureManager.loadFromFile("cursorUpgrade", "data/cursor/upgrade_cursor.png");
	textureManager.loadFromFile("cursorSell", "data/cursor/sell_cursor.png");

	soundManager.loadFromFile("mouseHover", "data/sfx/mouseover.ogg");
	soundManager.loadFromFile("mouseClick", "data/sfx/click.ogg");

	cursor.setTexture(textureManager.getTexture("cursorNormal"));

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

	//Cursor position
	cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

}

void Game::draw()
{
	window.clear(sf::Color(210, 210, 210));

	manager.draw();
	window.draw(cursor);

	window.display();
}

void Game::registerStates()
{
	manager.registerState<GameState>(States::ID::Game);
	manager.registerState<MenuState>(States::ID::Menu);
	manager.registerState<PauseState>(States::ID::Pause);
	manager.registerState<GameOverState>(States::ID::GameOver);
}
