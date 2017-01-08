#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>

class TextureManager
{
public:
	TextureManager();

	void loadFromFile(const std::string &name, const std::string &filename);

	sf::Texture &getTexture(const std::string &name);
private:
	std::map<std::string, sf::Texture> textures;
};

