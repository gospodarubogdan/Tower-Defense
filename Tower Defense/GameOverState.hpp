#pragma once

#include "State.hpp"
#include <SFML/Audio.hpp>

class GameOverState final : public State
{
public:
	explicit GameOverState(StateManager &stack, States::Context context);

	bool handleEvent(const sf::Event &event) override;
	bool update(sf::Time dt) override;
	void draw() override;

private:
	sf::Text gameOverText, highscoreText, enterText;
	sf::Music music;
};