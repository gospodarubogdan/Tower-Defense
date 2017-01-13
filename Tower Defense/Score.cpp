#include "Score.hpp"


Score::Score()
{
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(sf::Color(0, 0, 0));
}

void Score::setFont(const sf::Font &font)
{
	scoreText.setFont(font);
}

void Score::computeScore(int gold, int lives, int level)
{
	score = gold * level + lives * 2 + level * 10;
	scoreText.setString("Score: " + std::to_string(score));
}

const int Score::getScore() const
{
	return score;
}

sf::Vector2f Score::getSize() const
{
	return sf::Vector2f(scoreText.getLocalBounds().width, scoreText.getLocalBounds().height);
}

void Score::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(scoreText, states);
}
