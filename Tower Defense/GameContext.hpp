#pragma once

namespace sf
{
	class RenderWindow;
	class Font;
}
class TextureManager;

namespace States
{
	class Context
	{
	public:
		explicit Context(sf::RenderWindow &window, sf::Font &font, TextureManager &textureManager)
			: window(&window)
			, font(&font)
			, textureManager(&textureManager)
		{};

		sf::RenderWindow *window;
		sf::Font *font;
		TextureManager *textureManager;
	};
}