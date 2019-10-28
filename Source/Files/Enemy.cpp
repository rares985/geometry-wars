#include <iostream>

#include "Enemy.h"
#include "constants.h"
#include "Player.h"
#include "Projectile.h"

Enemy::Enemy(const std::string mesh_name, const glm::vec3& color, int initial_lives)
{
	this->mesh_name = mesh_name;
	this->color = color;
	this->initial_lives = initial_lives;
	this->lives_left = initial_lives;
	this->size = DEFAULT_ENEMY_SIZE;
}


Enemy::~Enemy() {

}

void Enemy::UpdatePosition(float speed_cuantif)
{
	this->tx += this->x_speed * speed_cuantif;
	this->ty += this->y_speed * speed_cuantif;
}

void Enemy::HandleCollisionWith(Enemy& enemy)
{
	// No collision possible between enemies...
}

void Enemy::HandleCollisionWith(Projectile& projectile)
{
	/* notify projectile that it collided with us */
	projectile.HandleCollisionWith(*this);

	/* take damage */
	this->TakeDamage(1);
}

void Enemy::HandleCollisionWith(Powerup& powerup)
{
	// No collision possible between enemy and powerup...
}

void Enemy::HandleCollisionWith(Player& player)
{
	/* notified by player, only take damage */

	/* Die */
	this->TakeDamage(this->lives_left);
}

void Enemy::PerformShrink(float deltaTimeSeconds)
{
	if (this->scale > 0.75f) {
		this->scale -= (0.5f * deltaTimeSeconds) / SHRINK_ANIMATION_DURATION; /* and it shrinks over 250ms to half size */
	}

	/* Doubles speed a LOT of times but only this way is it noticeable */
	this->setMeshName(SHRINKED_ENEMY_SHIP_MESH_NAME);
	this->x_speed *= 2;
	this->y_speed *= 2;
	this->setColor(firebrick);
}

int Enemy::getScorePoints(void)
{
	if (lives_left == 0) {
		return initial_lives;
	}
	return 0;
}

void Enemy::TakeDamage(int damage)
{
	this->lives_left -= damage;

	if (this->lives_left <= 0) {
		this->visible = false;
	}
	else if (this->lives_left == 1) {
		this->shrink = true;
	}
}
