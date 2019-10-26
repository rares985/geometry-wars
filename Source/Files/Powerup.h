#pragma once

#ifndef POWERUP_H_
#define POWERUP_H_

#include "GameObject.h"

class Powerup : public GameObject {
public:
	Powerup(int type);
	~Powerup();

	void collideWith(Enemy& enemy) override;
	void collideWith(Projectile& enemy) override;
	void collideWith(Powerup& enemy) override;
	void collideWith(Player& player) override;

private:
	int type;
};

#endif /* POWERUP_H_ */