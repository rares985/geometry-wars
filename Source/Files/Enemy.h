#pragma once

#ifndef ENEMY_H_
#define ENEMY_H_

#include "GameObject.h"

class Enemy : public GameObject {

public:
	Enemy(int enemy_type);
	~Enemy();

	void	collideWith(Enemy& enemy) override;
	void	collideWith(Projectile& projectile) override;
	void	collideWith(Powerup& powerup) override;
	void	collideWith(Player& player) override;

	void	updatePosition(float speed_cuantif);
	void	performShrink(float deltaTimeSeconds);

private:
	void	takeDamage(int damage);

};

#endif /* ENEMY_H_ */