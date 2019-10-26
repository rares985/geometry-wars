#include "Object2D.h"

#include "Player.h"
#include "constants.h"
#include "Enemy.h"
#include "Powerup.h"


Player::Player() {
	
	this->setSize(PLAYER_SIZE);
	this->setColor(ivory);

	this->mesh_name = "player_ship";
	this->center = origin;

	this->lives_left = 3;
	this->initial_lives = 3;
}

Player::~Player() {
	// deconstruct player class... 
}

void Player::updatePosition(float x_cuantif, float y_cuantif) {
	this->tx += x_cuantif;
	this->ty += y_cuantif;
}

void Player::collideWith(Enemy& enemy) {
	/* take Damage */
	this->takeDamage(enemy.getLivesLeft());

	/* Notify enemy that it collided with us, it will take damage */
	enemy.collideWith(*this);
}

void Player::collideWith(Projectile& enemy) {
	// no collision possible between player and projectile...
}

void Player::collideWith(Powerup& powerup) {
	/* Notify powerup that it collided with us...will apply an efect */
	powerup.collideWith(*this);

	/* Apply effect -- TODO freeze from here */
	if (powerup.getMeshName() == "life") {
		this->lives_left++;
	}

}

void Player::collideWith(Player& player) {
	// No collision possible between two players ...
}

void Player::takeDamage(int damage) {
	this->lives_left -= damage;
	if (this->lives_left <= 0) {
		this->visible = 0;
	}
}
