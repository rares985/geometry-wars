#pragma once

#ifndef ENEMY_FACTORY_H_
#define ENEMY_FACTORY_H_

#include <memory>


class Enemy;


enum class EnemyType {
	ET_NORMAL,
	ET_STRONG,
	ET_BOSS,
	ET_MAX_NO
};

class EnemyFactory {

public:
	static std::unique_ptr<Enemy> createEnemy(EnemyType type);
};


#endif /* ENEMY_FACTORY_H_ */
