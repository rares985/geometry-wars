#include "Object2D.h"

#include "Player.h"
#include "constants.h"


Player::Player() {
	
	this->setSize(PLAYER_SIZE);
	this->setColor(ivory);

	this->mesh_name = "player_ship";
	this->center = origin;

	this->lives_left = 3;
	this->initial_lives = 3;
}

Player::~Player()
{
}

void Player::updatePosition(float x_cuantif, float y_cuantif)
{
	this->tx += x_cuantif;
	this->ty += y_cuantif;
}
