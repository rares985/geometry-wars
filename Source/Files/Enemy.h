#pragma once

#ifndef ENEMY_H_
#define ENEMY_H_

#include "GameObject.h"

class Enemy : public GameObject {
public:
	Enemy(int enemy_type);
	~Enemy();

	void updatePosition(float speed_cuantif);

private:

};



#endif
