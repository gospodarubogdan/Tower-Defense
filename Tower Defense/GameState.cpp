#include "GameState.hpp"
#include "Constants.hpp"


GameState::GameState(StateManager &stack, States::Context context)
	: State(stack, context)
	, map(TILE_SIZE, TILE_WORLD_SIZE)
{
	//map.loadFromCSV("data/mapValues.csv");
	//map.loadSheet("data/mapsheet.png");
	textureManager.loadFromFile("mapSheet", "data/mapnospace.png");
	textureManager.getTexture("mapSheet").setSmooth(true);
	map.setTexture(textureManager.getTexture("mapSheet"));

	hud.setPosition(0.f, 400.f);
}

bool GameState::handleEvent(const sf::Event &event)
{
	return false;
}

bool GameState::update(sf::Time dt)
{
	return false;
}

void GameState::draw()
{
	getContext().window->draw(map);

	getContext().window->draw(hud);
}
