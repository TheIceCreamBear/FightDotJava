#include "Enemy.h"
#include "Constants.h"

Enemy::Enemy(Location loc, int health) {
	this->loc = loc;
	this->health = health;
}

void Enemy::update() {
	// TODO enemy movement
}

int Enemy::getDamageFromAttack() {
	// TODO Eventually have multiple attacks and critical hits
	return damage(Constants::rng);
}