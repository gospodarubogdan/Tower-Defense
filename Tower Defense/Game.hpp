#pragma once

#include "StateManager.hpp"
#include "GameContext.hpp"
#include "Camera.hpp"

class Game : sf::NonCopyable
{
public:
	Game();

	void run();

private:
	void processEvents();
	void update(sf::Time frameTime);
	void draw();

	void registerStates();

	sf::RenderWindow window;
	States::Context  context;
	Camera			 camera;
	StateManager     manager;
};

