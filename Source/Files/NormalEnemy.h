#pragma once

#ifndef NORMAL_ENEMY_H_
#define NORMAL_ENEMY_H_

#include "Enemy.h"
#include "constants.h"


class NormalEnemy : public Enemy {
public:
	NormalEnemy() : Enemy(WEAK_ENEMY_SHIP_MESH_NAME, deepskyblue, 1) {};
};


#endif /* NORMAL_ENEMY_H_ */
