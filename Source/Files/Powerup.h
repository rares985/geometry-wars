#pragma once

#ifndef POWERUP_H_
#define POWERUP_H_

#include "GameObject.h"

class Powerup : public GameObject {

public:

	Powerup(int type);
	~Powerup();

	void	handleCollisionWith(Enemy& enemy) override;
	void	handleCollisionWith(Projectile& projectile) override;
	void	handleCollisionWith(Powerup& powerup) override;
	void	handleCollisionWith(Player& player) override;

private:

	int		type;
};

#endif /* POWERUP_H_ */