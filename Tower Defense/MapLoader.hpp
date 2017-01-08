#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class MapLoader
{
public:
	MapLoader();
	
	void loadFromCSV(const std::string &filename);
	void loadSheet(const std::string &filename);

	sf::Image &getImage();
	int getTileID(const int index);
private:
	std::vector<int> mapValues;
	sf::Image mapSheet;
};

