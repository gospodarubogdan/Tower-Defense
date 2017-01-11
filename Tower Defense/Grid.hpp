#pragma once

#include "Tile.hpp"

class Grid
{
public:
	explicit Grid(sf::RenderWindow &window);
	~Grid() = default;

	void draw();

	Tile &getTile(int index);

private:
	void loadFromCSV(const std::string &filename);
	void addTile(int tile, int x, int y);

	sf::Texture texture;
	std::vector<int> mapValues;
	std::vector<Tile> tiles;
	sf::RenderWindow &window;
};

