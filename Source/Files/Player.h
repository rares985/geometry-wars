#pragma once

#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"

class Player : public GameObject {

public:

	Player();
	~Player();

	void	updatePosition(float x_cuantif, float y_cuantif);

	void	handleCollisionWith(Enemy& enemy) override;
	void	handleCollisionWith(Projectile& projectile) override;
	void	handleCollisionWith(Powerup& powerup) override;
	void	handleCollisionWith(Player& player) override;

	bool	isDead(void) const;


private:

	void	takeDamage(int damage);

};

#endif /* PLAYER_H_ */