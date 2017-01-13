#pragma once

namespace sf
{
	class RenderWindow;
	class Font;
	class Sprite;
}
class TextureManager;
class SoundManager;
class Score;

namespace World
{
	struct LevelData
	{
		int numberOfMinions;
		int goldPerMinion;
		int hp;
		bool immuneToSlow;
		float movementSpeed;
		bool levelOver;
	};

	struct GameData
	{
		int lives;
		int gold;
		int currentLevel;
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
			, sf::Sprite &cursor
			, Score &score)

			: window(&window)
			, font(&font)
			, textureManager(&textureManager)
			, soundManager(&soundManager)
			, cursor(&cursor)
			, score(&score)
		{};

		sf::RenderWindow *window;
		sf::Font *font;
		TextureManager *textureManager;
		SoundManager *soundManager;
		sf::Sprite *cursor;
		Score *score;
	};
}