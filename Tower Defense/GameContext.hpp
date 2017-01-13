#pragma once

namespace sf
{
	class RenderWindow;
	class Font;
	class Sprite;
}
class TextureManager;
class SoundManager;

namespace World
{
	struct LevelData
	{
		int numberOfMinions;
		int goldPerMinion;
		int hp;
		bool immuneToSlow;
		int movementSpeed;
		bool levelOver;
	};

	struct GameData
	{
		int lives;
		int gold;
	};

	struct UpgradeData
	{
		int cost[3];
		int damage[3];
		float attackSpeed[3];
	};
}

namespace States
{
	struct Context
	{
		explicit Context(sf::RenderWindow &window
			, sf::Font &font
			, TextureManager &textureManager
			, SoundManager &soundManager
			, sf::Sprite &cursor)

			: window(&window)
			, font(&font)
			, textureManager(&textureManager)
			, soundManager(&soundManager)
			, cursor(&cursor)
		{};

		sf::RenderWindow *window;
		sf::Font *font;
		TextureManager *textureManager;
		SoundManager *soundManager;
		sf::Sprite *cursor;
	};
}