#pragma once

#include "State.hpp"
#include "TextureManager.hpp"
#include "MapLoader.hpp"
#include "TileMap.hpp"
#include "HUD.hpp"
#include "Grid.hpp"
#include "EntityManager.hpp"
#include "Camera.hpp"
#include "TowerTypes.hpp"

#include "ShootSystem.hpp"
#include "MoveSystem.hpp"
#include "DrawSystem.hpp"

class GameState : public State
{
public:
	explicit GameState(StateManager &stack, States::Context context);
	~GameState() = default;

	bool handleEvent(const sf::Event &event) override;
	bool update(sf::Time dt) override;
	void draw() override;

private:
	void placeTower();
	bool validPosition();

	TextureManager textureManager;

	bool selected;
	Tower::Type tower;
	sf::RectangleShape placement;

	Camera camera;

	ShootSystem shootsystem;
	MoveSystem ms;
	DrawSystem ds;

	EntityManager entityManager;
	Grid grid;
	gui::HUD hud;
	//MapLoader map;
	sf::Texture texture;
	TileMap map;
};

