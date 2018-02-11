#include "Player.h"

Player::Player(float tx, float ty) {
	this->lives_left = 3;
	this->initial_lives = 3;

	this->tx = tx;
	this->ty = ty;
}