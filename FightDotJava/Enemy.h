#pragma once
#include "Location.h"
#include <random>
#include <string>

class Enemy {
public:
	Enemy(Location loc, std::string name, int health);
	void update();
	void damage(int amount);
	std::string getName();
	int getHealth() {
		return health;
	}
	int getDamageFromAttack();
	bool isDead() {
		return health == 0;
	}
private:
	std::uniform_int_distribution<int> damageRange = std::uniform_int_distribution<int>(5, 12);
	Location loc;
	std::string name;
	int health;
};