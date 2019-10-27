#include "Object2D.h"

#include "Player.h"
#include "constants.h"
#include "Enemy.h"
#include "Powerup.h"


Player::Player() {
	
	this->setSize(PLAYER_SIZE);
	this->setColor(ivory);

	this->mesh_name = PLAYER_SHIP_MESH_NAME;
	this->center = origin;

	this->lives_left = 3;
	this->initial_lives = 3;
}

Player::~Player() {
	// deconstruct player class... 
}

void Player::UpdatePosition(float x_cuantif, float y_cuantif) {
	this->tx += x_cuantif;
	this->ty += y_cuantif;
}

void Player::HandleCollisionWith(Enemy& enemy) {
	/* take Damage */
	this->TakeDamage(enemy.getLivesLeft());

	/* Notify enemy that it collided with us, it will take damage */
	enemy.HandleCollisionWith(*this);
}

void Player::HandleCollisionWith(Projectile& enemy) {
	// no collision possible between player and projectile...
}

void Player::HandleCollisionWith(Powerup& powerup) {
	/* Notify powerup that it collided with us...will apply an efect */
	powerup.HandleCollisionWith(*this);

	/* Apply effect -- TODO freeze from here */
	if (powerup.getMeshName() == "life") {
		this->lives_left++;
	}

}

void Player::HandleCollisionWith(Player& player) {
	// No collision possible between two players ...
}

bool Player::IsDead(void) const
{
	return (this->lives_left <= 0);
}

void Player::TakeDamage(int damage) {
	this->lives_left -= damage;
	if (this->lives_left <= 0) {
		this->visible = 0;
	}
}
