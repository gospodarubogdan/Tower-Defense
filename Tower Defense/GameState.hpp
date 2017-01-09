#pragma once

#include "State.hpp"
#include "TextureManager.hpp"
#include "MapLoader.hpp"
#include "TileMap.hpp"
#include "HUD.hpp"
#include "Grid.hpp"

class GameState : public State
{
public:
	explicit GameState(StateManager &stack, States::Context context);
	~GameState() = default;

	bool handleEvent(const sf::Event &event) override;
	bool update(sf::Time dt) override;
	void draw() override;

private:
	TextureManager textureManager;

	Grid grid;
	gui::HUD hud;
	//MapLoader map;
	sf::Texture texture;
	TileMap map;
};

