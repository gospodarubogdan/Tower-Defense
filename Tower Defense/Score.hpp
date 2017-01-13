#pragma once

#include <SFML/Graphics.hpp>

class Score : public sf::Drawable, public sf::Transformable
{
public:
	Score();

	void setFont(const sf::Font &font);

	void computeScore(int gold, int lives, int level);
	const int getScore() const;

	sf::Vector2f getSize() const;
private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	sf::Text scoreText;
	int score;
};

