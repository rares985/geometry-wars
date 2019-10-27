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
	GS_NOT_STARTED	= 0,
	GS_RUNNING		= 1,
	GS_FROZEN		= 2,
	GS_PAUSED		= 3,
	GS_ENDED		= 4,
	GS_INVALID		= 5
};

class GameInstance {

public:
	GameInstance();
	~GameInstance();

	void		UpdateScore(int diff);
	void		UpdateTimers(float deltaTimeSeconds);

	void		SpawnEnemies();
	void		SpawnPowerup();

	void		OnGameEnd(void) { game_state = GameState::GS_ENDED; };

	bool		IsFrozen(void) const { return game_state == GameState::GS_FROZEN; };
	bool		IsEnded(void) const { return game_state == GameState::GS_ENDED; };
	bool		IsRunning(void) const { return game_state == GameState::GS_RUNNING; };
	bool		IsPaused(void) const { return game_state == GameState::GS_PAUSED; };

	void		Freeze(void) { game_state = GameState::GS_FROZEN; freeze_timer = 0; };
	void		Thaw(void) { game_state = GameState::GS_RUNNING; freeze_timer = 0; };

	void		Pause(void) { game_state = GameState::GS_PAUSED; };
	void		Resume(void) { game_state = GameState::GS_RUNNING; };

	void		EraseInvisibleEntities();

	GameState	getGameState() const { return game_state; };

	float													freeze_timer;

	std::unique_ptr<Player>									player;

	std::list<std::unique_ptr<Enemy>>						enemies;
	std::list<std::unique_ptr<Projectile>>					projectiles;
	std::list<std::unique_ptr<Powerup>>						powerups;

private:
	long long int				score;

	float						time_elapsed;
	float						enemy_spawn_timer;
	float						enemy_spawn_threshold;
	float						powerup_spawn_timer;
	float						powerup_spawn_threshold;

	GameState					game_state;



};


#endif /* GAME_INSTANCE_H_ */