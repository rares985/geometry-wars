
#include "Powerup.h"
#include "constants.h"


Powerup::Powerup(int type) {
	this->type = type;
	if (type == 1) {
		this->mesh_name = "life";
		this->setColor(forestgreen);
		this->setSize(LIFE_POWERUP_SIZE);

	}
	if (type == 2) {
		this->mesh_name = "freeze";
		this->setColor(darkcyan);
		this->setSize(FREEZE_POWERUP_SIZE);
	}
}

Powerup::~Powerup() {
	// Deconstruct Powerup object

}

void Powerup::collideWith(Enemy& enemy)
{
	// No collision possible between enemies and powerups...
}

void Powerup::collideWith(Projectile& projectile) {
	// No collision possible betwen projectiles and powerups...
}

void Powerup::collideWith(Powerup& powerup){
	// No collision possible between powerups...
}

void Powerup::collideWith(Player& player)
{
	/* Notified by player, apply effect ? */
}
