#include "TextureManager.hpp"

TextureManager::TextureManager()
	: textures()
{
}

void TextureManager::loadFromFile(const std::string &name, const std::string &filename)
{
	sf::Texture texture;
	texture.loadFromFile(filename);

	textures[name] = texture;
}

sf::Texture &TextureManager::getTexture(const std::string &name)
{
	return textures.at(name);
}
