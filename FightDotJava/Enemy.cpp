#include "Enemy.h"
#include "Constants.h"

Enemy::Enemy(Location loc, int health) {
	this->loc = loc;
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

int Enemy::getDamageFromAttack() {
	// TODO Eventually have multiple attacks and critical hits
	return damageRange(Constants::rng);
}