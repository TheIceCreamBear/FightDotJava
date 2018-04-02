#pragma once
#include "Location.h"
#include <random>

class Enemy {
public:
	Enemy(Location loc, int health);
	void update();
	void damage(int amount);
	int getDamageFromAttack();
	bool isDead() {
		return health == 0;
	}
private:
	std::uniform_int_distribution<int> damageRange = std::uniform_int_distribution<int>(5, 20);
	Location loc;
	int health;
};