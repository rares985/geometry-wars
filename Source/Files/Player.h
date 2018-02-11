#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"

class Player : public GameObject {
	public:
		Player(float tx, float ty);
		~Player();
};
#endif /* PLAYER_H_ */
