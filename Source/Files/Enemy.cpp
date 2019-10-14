#include "Enemy.h"


Enemy::Enemy() {

}

Enemy::~Enemy() {

}

void Enemy::takeDamage(int damage) {
	this->lives_left -= damage;
	if (this->lives_left == 1) {
		this->shrink = true;
	}

	if (this->lives_left <= 0) {
		this->should_render = false;
	}
}