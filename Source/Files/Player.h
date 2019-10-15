#pragma once

#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"

class Player : public GameObject {

public:
	Player();
	~Player();

	void updatePosition(float x_cuantif, float y_cuantif);


private:

};



#endif /* PLAYER_H_ */