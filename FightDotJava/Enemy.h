#pragma once
#include "Location.h"
#include <random>

class Enemy {
	Enemy(Location loc, int health);
	void update();
	int getDamageFromAttack();
private:
	std::uniform_int_distribution<int> damage = std::uniform_int_distribution<int>(5, 20);
	Location loc;
	int health;
};