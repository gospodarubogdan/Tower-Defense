#pragma once

#include <SFML/Graphics.hpp>

class Gold
{
public:
	Gold();

	void addGold(int amount);

	const int getGold() const;

private:
	int totalGold;
};

