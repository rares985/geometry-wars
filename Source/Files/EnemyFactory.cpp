#include "EnemyFactory.h"
#include "Enemy.h"
#include <Files\NormalEnemy.h>
#include <Files\StrongEnemy.h>
#include <Files\BossEnemy.h>
#include <memory>

class EnemyTypeNotFoundException {};

std::unique_ptr<Enemy> EnemyFactory::createEnemy(EnemyType type)
{
	switch (type) {
	case EnemyType::ET_NORMAL:
		return std::make_unique<NormalEnemy>();
		break;
	case EnemyType::ET_STRONG:
		return std::make_unique<StrongEnemy>();
		break;
	case EnemyType::ET_BOSS:
		return std::make_unique<BossEnemy>(BOSS_ENEMY_SIZE);
		break;
	default:
		throw new EnemyTypeNotFoundException();
	}
}
