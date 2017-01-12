#pragma once

namespace sf
{
	class RenderWindow;
	class Font;
}
class TextureManager;
class Gold;

namespace States
{
	class Context
	{
	public:
		explicit Context(sf::RenderWindow &window
			, sf::Font &font
			, TextureManager &textureManager
			, Gold &gold)

			: window(&window)
			, font(&font)
			, textureManager(&textureManager)
			, gold(&gold)
		{};

		sf::RenderWindow *window;
		sf::Font *font;
		TextureManager *textureManager;
		Gold *gold;
	};
}