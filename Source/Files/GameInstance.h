#pragma once

#ifndef GAME_INSTANCE_H_
#define GAME_INSTANCE_H_

#include <chrono>
#include <list>
#include "Enemy.h"
#include "Player.h"
#include "Powerup.h"
#include "Projectile.h"

enum class GameState {
	GS_NOT_STARTED = 0,
	GS_RUNNING = 1,
	GS_FROZEN = 2,
	GS_ENDED = 3,
	GS_INVALID = 4
};

class GameInstance {
public:
	GameInstance();
	~GameInstance();

	void updateScore(int diff);
	void updateTimers(float deltaTimeSeconds);

	bool isEndGame(void);

	void OnGameEnd(void);

	void spawnEnemies();

	void spawnPowerup();

private:
	long long int score;
	bool end_game;
	bool freeze_enemies;

	float time_elapsed;
	float enemy_spawn_timer;
	float enemy_spawn_threshold;
	float powerup_spawn_timer;
	float powerup_spawn_threshold;
	float freeze_timer;

	GameState game_state;

	Player* player;
	std::list<Enemy*> enemies;
	std::list<Projectile*> projectiles;
	std::list<Powerup*> powerups;


};


#endif /* GAME_INSTANCE_H_ */
