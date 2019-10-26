#pragma once

#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"

class Player : public GameObject {

public:
	Player();
	~Player();

	void updatePosition(float x_cuantif, float y_cuantif);

	void collideWith(Enemy& enemy) override;
	void collideWith(Projectile& projectile) override;
	void collideWith(Powerup& powerup) override;
	void collideWith(Player& player) override;


private:

	void takeDamage(int damage);

};



#endif /* PLAYER_H_ */