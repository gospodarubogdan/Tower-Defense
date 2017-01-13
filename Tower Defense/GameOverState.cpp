#include "GameOverState.hpp"
#include "Score.hpp"

#include <fstream>

GameOverState::GameOverState(StateManager &stack, States::Context context)
	: State(stack, context)
{
	sf::RenderWindow &window = *context.window;
	sf::Font &font = *context.font;

	music.openFromFile("data/gameover.ogg");
	music.play();
	
	gameOverText.setString("GAME OVER");
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setCharacterSize(100);
	gameOverText.setFont(font);
	gameOverText.setPosition({ std::floor(window.getSize().x / 2 - gameOverText.getLocalBounds().width / 2),
		std::floor(window.getSize().y / 2 - gameOverText.getLocalBounds().height * 1.5f) });
	
	Score &score = *context.score;
	score.setPosition({ std::floor(window.getSize().x / 2 - score.getSize().x / 2),
		std::floor(window.getSize().y / 2 - score.getSize().y * 2) });

	std::ifstream fin("highscore.txt");
	int highscore = 0;
	fin >> highscore;
	fin.close();

	std::ofstream fout("highscore.txt");
	if (highscore < score.getScore())
		highscore = score.getScore();
	fout << highscore;
	fout.close();

	highscoreText.setString("Highscore: " + std::to_string(highscore));
	highscoreText.setFillColor(sf::Color::Black);
	highscoreText.setCharacterSize(20);
	highscoreText.setFont(font);
	highscoreText.setPosition({ std::floor(window.getSize().x / 2 - highscoreText.getLocalBounds().width / 2),
		std::floor(window.getSize().y / 2 + highscoreText.getLocalBounds().height) });

	enterText.setString("ENTER Menu");
	enterText.setFillColor(sf::Color::Black);
	enterText.setCharacterSize(30);
	enterText.setFont(font);
	enterText.setPosition({ std::floor(window.getSize().x / 2 - enterText.getLocalBounds().width / 2),
		std::floor(window.getSize().y / 2 + enterText.getLocalBounds().height * 5) });
}

bool GameOverState::handleEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed
		&& event.key.code == sf::Keyboard::Return)
	{
		popState();
		pushState(States::ID::Menu);
	}

	return false;
}

bool GameOverState::update(sf::Time dt)
{
	return false;
}

void GameOverState::draw()
{
	sf::RenderWindow &window = *getContext().window;
	window.setView(window.getDefaultView());
	window.draw(gameOverText);
	window.draw(*getContext().score);
	window.draw(highscoreText);
	window.draw(enterText);
}