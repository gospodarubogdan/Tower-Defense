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
	void placeTower(Tower::Type type);
	bool validPosition();

	void readLevelData();

	struct LevelData
	{
		int numberOfMinions;
		int goldPerMinion;
		int hp;
		bool immuneToSlow;
		int movementSpeed;
	};

	std::vector<LevelData> levelsData;

	bool selected;
	Tower::Type tower;
	sf::RectangleShape placement;
	sf::CircleShape range;

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

