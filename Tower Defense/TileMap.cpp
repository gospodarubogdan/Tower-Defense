#include "TileMap.hpp"
#include "Constants.hpp"

#include <fstream>

TileMap::TileMap(float tileSize, float tileWorldSize)
	: vertexArray(sf::PrimitiveType::Quads, MAP_WIDTH * MAP_HEIGHT * 4)
	, texture(nullptr)
	, tileSize(tileSize)
	, tileWorldSize(tileWorldSize)
{
	loadFromCSV("data/map.csv");

	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			int tileNumber = mapValues[y * MAP_WIDTH + x];
			addTileVertices(tileNumber % 19, tileNumber / 19, { static_cast<float>(x), static_cast<float>(y) });
		}
	}
}

void TileMap::loadFromCSV(const std::string &filename)
{
	std::ifstream fin(filename);

	char comma;
	int tileNumber;

	for (auto i = 0; i < MAP_WIDTH; i++)
	{
		for (auto j = 0; j < MAP_HEIGHT; j++)
		{
			fin >> tileNumber;
			mapValues.push_back(tileNumber);

			fin >> comma;
		}
	}

	fin.close();
}

void TileMap::setTexture(const sf::Texture &texture)
{
	this->texture = &texture;
	//this->texture->setSmooth(false);
}

void TileMap::addTileVertices(int x, int y, sf::Vector2f position)
{
	sf::Vertex vertex;

	vertex.position = (sf::Vector2f{ 0.0f, 0.0f } + position) * tileWorldSize;
	vertex.texCoords = sf::Vector2f{ tileSize * x, tileSize * y };
	vertexArray.append(vertex);

	vertex.position = (sf::Vector2f{ 1.0f, 0.0f } + position) * tileWorldSize;
	vertex.texCoords = sf::Vector2f{ tileSize * x + tileSize, tileSize * y };
	vertexArray.append(vertex);

	vertex.position = (sf::Vector2f{ 1.0f, 1.0f } + position) * tileWorldSize;
	vertex.texCoords = sf::Vector2f{ tileSize * x + tileSize, tileSize * y + tileSize };
	vertexArray.append(vertex);

	vertex.position = (sf::Vector2f{ 0.0f, 1.0f } + position) * tileWorldSize;
	vertex.texCoords = sf::Vector2f{ tileSize * x, tileSize * y + tileSize };
	vertexArray.append(vertex);
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.texture = texture;
	target.draw(vertexArray, states);
}
