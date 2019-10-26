#pragma once

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "GameObject.h"

class Projectile : public GameObject {

public:

	Projectile();
	~Projectile();

	void	updatePosition(float speed_cuantif);

	void	handleCollisionWith(Enemy& enemy) override;
	void	handleCollisionWith(Projectile& projectile) override;
	void	handleCollisionWith(Powerup& powerup) override;
	void	handleCollisionWith(Player& player) override;

};

#endif /* PROJECTILE_H_ */