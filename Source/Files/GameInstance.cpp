#include "GameInstance.h"
#include "constants.h"
#include <iostream>


GameInstance::GameInstance() {
	this->score = 0;

	this->game_state = GameState::GS_RUNNING;

	this->time_elapsed = 0.0f;
	this->enemy_spawn_timer = 0.0f;
	enemy_spawn_threshold = INITIAL_SPAWN_TIME;
	this->powerup_spawn_timer = 0.0f;
	this->powerup_spawn_threshold = 0.0f;
	this->freeze_timer = 0.0f;

	this->player = new Player();

}

GameInstance::~GameInstance() {
	for (auto obj : enemies) {
		delete obj;
	}
	for (auto obj : powerups) {
		delete obj;
	}
	for (auto obj : projectiles) {
		delete obj;
	}
}

void GameInstance::updateScore(int diff) {
	this->score += diff;

	printf("Score: %llu\n", this->score);
}

void GameInstance::updateTimers(float deltaTimeSeconds) {

	if (isRunning()) {
		enemy_spawn_timer += deltaTimeSeconds;
		powerup_spawn_timer += deltaTimeSeconds;

		/* The spawn threshold decreases per frame, from 2s to 0.5s */
		if (enemy_spawn_threshold > MIN_SPAWN_TIME) {
			enemy_spawn_threshold -= (deltaTimeSeconds / 100);
		}
		else if (enemy_spawn_threshold < MIN_SPAWN_TIME) {
			enemy_spawn_threshold = MIN_SPAWN_TIME;
		}

		/* Enemies spawn every spawn_threshold seconds*/
		if (enemy_spawn_timer > enemy_spawn_threshold) {
			spawnEnemies();
			enemy_spawn_timer = 0;
		}

		/* Powerups spawn every 10 seconds */
		if (powerup_spawn_timer > POWERUP_SPAWN_THRESHOLD) {
			powerup_spawn_timer = 0;
			spawnPowerup();
		}
	}

	/* If freeze is over, reset the timer */
	if (freeze_timer > FREEZE_DURATION) {
		unfreezeGame();
		freeze_timer = 0;
	}
}

void GameInstance::spawnEnemies() {
	for (int i = 0; i < ENEMIES_SPAWNED_PER_ROUND; i++) {

		float angle = (float)rand();
		glm::vec2 player_pos = player->getPosition();
		glm::vec2 polar_pos(cos(angle), sin(angle));

		/* Convert from angle to distance */
		polar_pos *= ENEMY_SPAWN_DISTANCE;

		int enemy_type = (rand() % 2) + 1;
		Enemy* enemy = new Enemy(enemy_type);

		enemy->setInitialPosition(player_pos + polar_pos);
		enemy->moveTowards(player_pos);

		float speedCuantifier = (float)(rand() % 3 + 1);

		enemy->x_speed *= speedCuantifier;
		enemy->y_speed *= speedCuantifier;

		enemies.push_back(enemy);
	}
}

void GameInstance::spawnPowerup() {

	int powerup_type = (rand() % 2 + 1);

	float x_pos = (float)(rand() % LOGIC_WINDOW_WIDTH);
	float y_pos = (float)(rand() % LOGIC_WINDOW_HEIGHT);

	Powerup* powerup = new Powerup(powerup_type);

	powerup->setCenter(origin);
	powerup->setInitialPosition(x_pos, y_pos);

	powerups.push_back(powerup);
}