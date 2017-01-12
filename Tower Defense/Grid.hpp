#pragma once

#include "Tile.hpp"

class Grid
{
public:
	explicit Grid(sf::RenderWindow &window);
	~Grid() = default;

	void draw();

	Tile &getTile(int i, int j);

private:
	void loadFromCSV(const std::string &filename);
	void addTile(int tile, int x, int y);

	sf::Texture texture;
	std::vector<int> mapValues;
	std::vector<Tile> tiles;
	std::vector<std::vector<Tile>> matrix;
	sf::RenderWindow &window;
};

