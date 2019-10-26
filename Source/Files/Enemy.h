#pragma once

#ifndef ENEMY_H_
#define ENEMY_H_

#include "GameObject.h"

class Enemy : public GameObject {
public:
	Enemy(int enemy_type);
	~Enemy();

	void updatePosition(float speed_cuantif);

	void collideWith(Enemy& enemy) override;
	void collideWith(Projectile& enemy) override;
	void collideWith(Powerup& enemy) override;
	void collideWith(Player& player) override;

private:

};



#endif
