#include <fstream>

#include "Grid.hpp"
#include "Constants.hpp"
#include <iostream>
Grid::Grid(sf::RenderWindow &window)
	: window(window)
{
	texture.loadFromFile("data/mapnospace.png");
	texture.setSmooth(true);
	//grid.resize(m_size.x, std::vector<Cell>(m_size.y));
	matrix.resize(MAP_HEIGHT, std::vector<Tile>(MAP_WIDTH));
	tiles.reserve(MAP_WIDTH * MAP_HEIGHT);
	mapValues.reserve(MAP_WIDTH * MAP_HEIGHT);
	loadFromCSV("data/map.csv");

	//for (int x = 0; x < MAP_WIDTH; x++)
	//{
	//	for (int y = 0; y < MAP_HEIGHT; y++)
	//	{
	//		int tileNumber = mapValues[y * MAP_WIDTH + x];
	//		std::cout << y * MAP_WIDTH + x << " ";
	//		addTile(tileNumber, x, y);
	//	}
	//}
}

void Grid::draw()
{
	/*for (const auto &tile : tiles)
		window.draw(tile);*/

	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			window.draw(matrix[i][j]);
}

Tile &Grid::getTile(int i, int j)
{
	return matrix[i][j];
}

void Grid::loadFromCSV(const std::string &filename)
{
	std::ifstream fin(filename);

	char comma;
	int tileNumber;

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			fin >> tileNumber;
			mapValues.push_back(tileNumber);
			//addTile(tileNumber, j, i);
			matrix[i][j].setTileNumber(tileNumber);
			sf::IntRect rect{ TILE_SIZE * (tileNumber % 19), TILE_SIZE * (tileNumber / 19), TILE_SIZE, TILE_SIZE };
			matrix[i][j].setTexture(texture, rect);
			matrix[i][j].setPosition(j * TILE_SIZE, i * TILE_SIZE);

			if (tileNumber == 266) matrix[i][j].setState(Tile::Type::Valid);
			else matrix[i][j].setState(Tile::Type::Invalid);

			fin >> comma;
		}
	}

	fin.close();
}

void Grid::addTile(int tile, int x, int y)
{
	tiles.emplace_back();

	sf::IntRect rect{TILE_SIZE * (tile % 19), TILE_SIZE * (tile / 19), TILE_SIZE, TILE_SIZE};

	tiles.back().setTexture(texture, rect);
	tiles.back().setPosition(x * TILE_SIZE, y * TILE_SIZE);

	// HARD CODED
	if(tile == 266) tiles.back().setState(Tile::Type::Valid);
	else tiles.back().setState(Tile::Type::Invalid);
}
