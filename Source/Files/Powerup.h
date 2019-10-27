#pragma once

#ifndef POWERUP_H_
#define POWERUP_H_

#include "GameObject.h"

class Powerup : public GameObject {

public:

	Powerup(int type);
	~Powerup();

	void	HandleCollisionWith(Enemy& enemy) override;
	void	HandleCollisionWith(Projectile& projectile) override;
	void	HandleCollisionWith(Powerup& powerup) override;
	void	HandleCollisionWith(Player& player) override;

private:

	int		type;
};

#endif /* POWERUP_H_ */