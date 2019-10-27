#pragma once

#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"

class Player : public GameObject {

public:

	Player();
	~Player();

	void	UpdatePosition(float x_cuantif, float y_cuantif);

	void	HandleCollisionWith(Enemy& enemy) override;
	void	HandleCollisionWith(Projectile& projectile) override;
	void	HandleCollisionWith(Powerup& powerup) override;
	void	HandleCollisionWith(Player& player) override;

	bool	IsDead(void) const;


private:

	void	TakeDamage(int damage);

};

#endif /* PLAYER_H_ */