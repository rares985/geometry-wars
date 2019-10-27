#include "Projectile.h"
#include "constants.h"
#include <iostream>

Projectile::Projectile() {
	this->mesh_name = PROJECTILE_MESH_NAME;
	this->setSize(PROJECTILE_SIZE);
	this->setCenter(origin);
	this->setColor(yellow);

}

Projectile::~Projectile() {

}

void Projectile::updatePosition(float speed_cuantif) {
	this->tx += this->x_speed * speed_cuantif;
	this->ty += this->y_speed * speed_cuantif;
}

void Projectile::handleCollisionWith(Enemy& enemy) {
	/* Notified by enemy */

	/* Disappear */
	this->visible = false;

}

void Projectile::handleCollisionWith(Projectile& projectile) {
	// No collision possible between projectiles...
}

void Projectile::handleCollisionWith(Powerup& powerup) {
	// No collision possible between powerups and projectiles...
}

void Projectile::handleCollisionWith(Player& player) {
	// No collision possible between projectile and player...
}
