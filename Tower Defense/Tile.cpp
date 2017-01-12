#include "Tile.hpp"

Tile::Tile()
	: state(Tile::Type::None)
{
}

Tile::~Tile()
{
}

void Tile::setState(Type state)
{
	this->state = state;
}

void Tile::setTexture(const sf::Texture &texture, sf::IntRect rect)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
}

void Tile::setTileNumber(int number)
{
	tileNumber = number;
}

const Tile::Type Tile::getState() const
{
	return state;
}

const int Tile::getTileNumber() const
{
	return tileNumber;
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}
