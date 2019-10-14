#pragma once

#ifndef ENEMY_H_
#define ENEMY_H_

#include "GameObject.h"

class Enemy : public GameObject {
public:
	Enemy();
	~Enemy();

	void takeDamage(int damage);

private:

};



#endif
