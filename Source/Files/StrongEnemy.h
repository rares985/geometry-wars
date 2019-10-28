#pragma once
#ifndef STRONG_ENEMY_H_
#define STRONG_ENEMY_H_

#include "Enemy.h"
#include "constants.h"


class StrongEnemy : public Enemy {
public:
	StrongEnemy() : Enemy(STRONG_ENEMY_SHIP_MESH_NAME, gold, 2) {};
};

#endif /* STRONG_ENEMY_H_ */
