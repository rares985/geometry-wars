
#include "Powerup.h"
#include "constants.h"


Powerup::Powerup(int type) {
	this->type = type;
	if (type == 1) {
		this->mesh_name = LIFE_POWERUP_MESH_NAME;
		this->setColor(forestgreen);
		this->setSize(LIFE_POWERUP_SIZE);

	}
	if (type == 2) {
		this->mesh_name = FREEZE_POWERUP_MESH_NAME;
		this->setColor(darkcyan);
		this->setSize(FREEZE_POWERUP_SIZE);
	}
}

Powerup::~Powerup() {
	// Deconstruct Powerup object

}

void Powerup::handleCollisionWith(Enemy& enemy)
{
	// No collision possible between enemies and powerups...
}

void Powerup::handleCollisionWith(Projectile& projectile) {
	// No collision possible betwen projectiles and powerups...
}

void Powerup::handleCollisionWith(Powerup& powerup){
	// No collision possible between powerups...
}

void Powerup::handleCollisionWith(Player& player)
{
	/* Notified by player, apply effect ? */

	/* disappear */
	this->visible = false;
}
