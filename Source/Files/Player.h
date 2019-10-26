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
	void collideWith(Projectile& enemy) override;
	void collideWith(Powerup& enemy) override;
	void collideWith(Player& player) override;


private:

};



#endif /* PLAYER_H_ */