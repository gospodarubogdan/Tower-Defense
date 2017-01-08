#include "MapLoader.hpp"
#include "Constants.hpp"

#include <fstream>

MapLoader::MapLoader()
	: mapValues()
{
}

void MapLoader::loadFromCSV(const std::string &filename)
{
	std::ifstream fin(filename);

	char comma;
	int tileNumber;
	
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			fin >> tileNumber;
			mapValues.push_back(tileNumber);

			fin >> comma;
		}
	}

	fin.close();
}

void MapLoader::loadSheet(const std::string &filename)
{
	mapSheet.loadFromFile(filename);
}

sf::Image &MapLoader::getImage()
{
	return mapSheet;
}

int MapLoader::getTileID(const int index)
{
	return mapValues.at(index);
}
