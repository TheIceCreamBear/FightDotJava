#include "Enemy.h"
#include "Constants.h"

Enemy::Enemy(Location loc, std::string name, int health) {
	this->loc = loc;
	this->name = name;
	this->health = health;
}

void Enemy::update() {
	// TODO enemy movement
}

void Enemy::damage(int amount) {
	this->health -= amount;
	if (health < 0) {
		health = 0;
	}
}

std::string Enemy::getName() {
	return name;
}

int Enemy::getDamageFromAttack() {
	// TODO Eventually have multiple attacks and critical hits
	return damageRange(Constants::rng);
}