#pragma once

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "GameObject.h"

class Projectile : public GameObject {
public:
	Projectile();
	~Projectile();

	void updatePosition(float speed_cuantif);

	void collideWith(Enemy& enemy) override;
	void collideWith(Projectile& enemy) override;
	void collideWith(Powerup& enemy) override;
	void collideWith(Player& player) override;
private:

};

#endif /* PROJECTILE_H_ */
