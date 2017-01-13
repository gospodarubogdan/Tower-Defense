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
#include "Gui.hpp"

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

	void freeTiles(const sf::Vector2f &position);
	void createLevelEntities();
	void readGameData();
	void upgradeEntity(Entity *entity);


	std::vector<World::UpgradeData> upgrades;
	World::GameData gameData;
	std::vector<World::LevelData> levelsData;
	int currentLevel;

	sf::Time waitingTime;

	bool selected;
	Tower::Type tower;
	sf::RectangleShape placement;
	sf::CircleShape range;

	Camera camera;

	gui::Gui container;
	
	EntityManager entityManager;
	Grid grid;
	gui::HUD hud;
	//MapLoader map;
	sf::Texture texture;
	TileMap map;

	sf::Text countdown;
};

