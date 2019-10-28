
#include "Powerup.h"
#include "constants.h"


Powerup::Powerup(int type) {

}

Powerup::~Powerup() {
	// Deconstruct Powerup object

}

void Powerup::HandleCollisionWith(Enemy& enemy)
{
	// No collision possible between enemies and powerups...
}

void Powerup::HandleCollisionWith(Projectile& projectile) {
	// No collision possible betwen projectiles and powerups...
}

void Powerup::HandleCollisionWith(Powerup& powerup){
	// No collision possible between powerups...
}

void Powerup::HandleCollisionWith(Player& player)
{
	/* Notified by player, apply effect ? */

	/* disappear */
	this->visible = false;
}
