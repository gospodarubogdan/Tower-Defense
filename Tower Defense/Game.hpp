#pragma once

#include "StateManager.hpp"
#include "GameContext.hpp"
#include "Camera.hpp"
#include "TextureManager.hpp"
#include "SoundManager.hpp"
#include "Score.hpp"

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

	sf::Font       font;
	TextureManager textureManager;
	SoundManager soundManager;

	sf::Sprite cursor;
	Score score;

	sf::RenderWindow window;
	States::Context  context;
	Camera			 camera;
	StateManager     manager;
};

