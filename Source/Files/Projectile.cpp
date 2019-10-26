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

void Projectile::updatePosition(float speed_cuantif)
{
	this->tx += this->x_speed * speed_cuantif;
	this->ty += this->y_speed * speed_cuantif;
}

void Projectile::collideWith(Enemy& enemy)
{
}

void Projectile::collideWith(Projectile& enemy)
{
}

void Projectile::collideWith(Powerup& enemy)
{
}

void Projectile::collideWith(Player& player)
{
}
