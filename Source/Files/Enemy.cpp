#include "Enemy.h"
#include "constants.h"
#include "Player.h"
#include "Projectile.h"
#include <iostream>

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
	this->initial_lives = enemy_type; /* Ugly hack, TODO remove */
	this->lives_left = this->initial_lives;

}

Enemy::~Enemy() {

}

void Enemy::updatePosition(float speed_cuantif)
{
	this->tx += this->x_speed * speed_cuantif;
	this->ty += this->y_speed * speed_cuantif;
}

void Enemy::collideWith(Enemy& enemy)
{
	// No collision possible between enemies...
}

void Enemy::collideWith(Projectile& projectile)
{
	/* notify projectile that it collided with us */
	projectile.collideWith(*this);

	/* take damage */
	this->takeDamage(1);
}

void Enemy::collideWith(Powerup& powerup)
{
	// No collision possible between enemy and powerup...
}

void Enemy::collideWith(Player& player)
{
	/* notified by player, only take damage */

	/* Die */
	this->takeDamage(this->lives_left);
}

void Enemy::performShrink(float deltaTimeSeconds)
{
	if (this->scale > 0.75f)
		this->scale -= (0.5f * deltaTimeSeconds) / SHRINK_ANIMATION_DURATION; /* and it shrinks over 250ms to half size */
}

void Enemy::takeDamage(int damage)
{
	this->lives_left -= damage;

	if (this->lives_left <= 0) {
		this->visible = false;
	}
	else if (this->lives_left == 1) {
		this->shrink = true;

		this->setMeshName("shrinked_enemy_ship");
		this->x_speed *= 2;
		this->y_speed *= 2;
		this->setColor(firebrick);
	}
}
