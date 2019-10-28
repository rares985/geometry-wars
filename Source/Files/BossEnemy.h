#pragma once

#ifndef BOSS_ENEMY_H_
#define BOSS_ENEMY_H_

#include "Enemy.h"
#include "constants.h"

class BossEnemy : public Enemy {
public:
	BossEnemy() : Enemy(BOSS_ENEMY_SHIP_MESH_NAME, pink, 4) {};
};
#endif /* BOSS_ENEMY_H_ */