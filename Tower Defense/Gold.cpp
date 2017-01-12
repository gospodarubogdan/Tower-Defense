#include "Gold.hpp"

Gold::Gold()
	: totalGold(150)
{
}

void Gold::addGold(int amount)
{
	totalGold += amount;
}

const int Gold::getGold() const
{
	return totalGold;
}
