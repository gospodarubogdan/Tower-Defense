#pragma once

#include <SFML/Graphics.hpp>

class Tile : public sf::Drawable, public sf::Transformable
{
public:
	enum class Type
	{
		None = 0,
		Invalid,
		Valid
	};

	Tile();
	~Tile();

	void setState(Type state);
	void setTexture(const sf::Texture &texture, sf::IntRect rect);

	const Type getState() const;

private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	Type state;
	sf::Sprite sprite;
	sf::Vector2i position;
};

