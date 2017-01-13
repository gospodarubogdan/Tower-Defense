#include "MenuState.hpp"
#include "Button.hpp"
#include "TextureManager.hpp"

#include <memory>

MenuState::MenuState(StateManager &stack, States::Context context)
	: State(stack, context)
{
	sf::RenderWindow &window = *getContext().window;

	title.setFont(*getContext().font);
	title.setFillColor(sf::Color::White);
	title.setCharacterSize(25);
	title.setString("Tower Defense");
	title.setPosition({ window.getSize().x / 2 - title.getLocalBounds().width / 2,
		window.getSize().y / 2 - title.getLocalBounds().height * 2.25f });

	sf::Texture &panelTexture = getContext().textureManager->getTexture("panel");
	panelSprite.setTexture(panelTexture);
	panelSprite.setPosition({ static_cast<float>(window.getSize().x / 2 - panelTexture.getSize().x / 2),
		static_cast<float>(window.getSize().y / 2 - panelTexture.getSize().y / 2) });

	auto play = std::make_shared<gui::Button>(*getContext().soundManager);// (*getContext().soundPlayer);
	play->setTexture(getContext().textureManager->getTexture("buttonGreen"));
	play->setPosition({ static_cast<float>(window.getSize().x / 2 - 190 / 2),
		static_cast<float>(window.getSize().y / 2 - 49 / 4 * 3) });
	play->setFont(*getContext().font);
	play->setText("Play");
	play->setCallback([this]()
	{
		popState();
		pushState(States::ID::Game);
	});

	auto quit = std::make_shared<gui::Button>(*getContext().soundManager);// (*getContext().soundPlayer);
	quit->setTexture(getContext().textureManager->getTexture("buttonRed"));
	quit->setPosition({ static_cast<float>(window.getSize().x / 2 - 190 / 2),
		static_cast<float>(window.getSize().y / 2 + 49 / 4 * 3) });
	quit->setFont(*getContext().font);
	quit->setText("Quit");
	quit->setCallback([this]()
	{
		popState();
	});

	container.addWidget(play);
	container.addWidget(quit);
}

bool MenuState::handleEvent(const sf::Event &event)
{
	container.handleWidgetsEvent(event);
	return false;
}

bool MenuState::update(sf::Time dt)
{
	container.updateWidgets(dt);
	return false;
}

void MenuState::draw()
{
	getContext().window->draw(panelSprite);
	getContext().window->draw(title);
	getContext().window->draw(container);
}