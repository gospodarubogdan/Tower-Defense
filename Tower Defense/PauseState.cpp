#include "PauseState.hpp"

PauseState::PauseState(StateManager &stack, States::Context context)
	: State(stack, context)
{
	sf::Font &font = *context.font;
	sf::RenderWindow &window = *context.window;

	pausedText.setString("PAUSE");
	pausedText.setCharacterSize(50);
	pausedText.setFont(font);
	pausedText.setPosition({ window.getSize().x / 2 - pausedText.getLocalBounds().width / 2,
		window.getSize().y / 2 - pausedText.getLocalBounds().height });

	enterText.setString("ENTER Menu");
	enterText.setCharacterSize(15);
	enterText.setFont(font);
	enterText.setPosition({ window.getSize().x - enterText.getLocalBounds().width - 20,
		window.getSize().y - enterText.getLocalBounds().height * 3 });

	escText.setString("ESC Resume");
	escText.setCharacterSize(15);
	escText.setFont(font);
	escText.setPosition({ 20, window.getSize().y - escText.getLocalBounds().height * 3 });

	background.setSize(static_cast<sf::Vector2f>(window.getSize()));
	background.setPosition({ 0,0 });
	background.setFillColor(sf::Color(0, 0, 0, 150));
}

bool PauseState::handleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			popState();
		}
		else if (event.key.code == sf::Keyboard::Return)
		{
			clearStates();
			pushState(States::ID::Menu);
		}
	}

	return false;
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

void PauseState::draw()
{
	sf::RenderWindow &window = *getContext().window;
	window.draw(background);
	window.draw(pausedText);
	window.draw(enterText);
	window.draw(escText);
}