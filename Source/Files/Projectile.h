#pragma once

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "GameObject.h"

class Projectile : public GameObject {

public:

	Projectile();
	~Projectile();

	void	UpdatePosition(float speed_cuantif);

	void	HandleCollisionWith(Enemy& enemy) override;
	void	HandleCollisionWith(Projectile& projectile) override;
	void	HandleCollisionWith(Powerup& powerup) override;
	void	HandleCollisionWith(Player& player) override;

};

#endif /* PROJECTILE_H_ */