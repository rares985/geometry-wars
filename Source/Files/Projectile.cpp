#include "Projectile.h"
#include "constants.h"

Projectile::Projectile() {
	this->mesh_name = "projectile";
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

void Projectile::collideWith(Enemy& enemy) {
	/* Notified by enemy */

	/* Disappear */
	this->visible = false;
}

void Projectile::collideWith(Projectile& projectile) {
	// No collision possible between projectiles...
}

void Projectile::collideWith(Powerup& powerup) {
	// No collision possible between powerups and projectiles...
}

void Projectile::collideWith(Player& player) {
	// No collision possible between projectile and player...
}
