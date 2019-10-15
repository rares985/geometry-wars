#include "Enemy.h"
#include "constants.h"

Enemy::Enemy(int enemy_type) {
	if (enemy_type == 1) {
		this->mesh_name = "weak_enemy_ship";
		this->setColor(deepskyblue);
	}
	else {
		this->mesh_name = "strong_enemy_ship";
		this->setColor(gold);
	}
	this->setSize(DEFAULT_ENEMY_SIZE);
	this->initial_lives = enemy_type;
	this->lives_left = this->initial_lives;
}

Enemy::~Enemy() {

}

void Enemy::updatePosition(float speed_cuantif)
{
	this->tx += this->x_speed * speed_cuantif;
	this->ty += this->y_speed * speed_cuantif;
}
