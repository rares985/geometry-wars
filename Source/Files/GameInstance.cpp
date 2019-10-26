#include "GameInstance.h"
#include "constants.h"
#include <cstdio>


GameInstance::GameInstance() {
	this->score = 0;
	this->end_game = false;

	this->game_state = GameState::GS_NOT_STARTED;

	this->time_elapsed = 0.0f;
	this->enemy_spawn_timer = 0.0f;
	this->enemy_spawn_threshold = 0.0f;
	this->powerup_spawn_timer = 0.0f;
	this->powerup_spawn_threshold = 0.0f;
	this->freeze_timer = 0.0f;

	this->freeze_enemies = false;
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

void GameInstance::updateTimers(float deltaTimeSeconds)
{
	if (!freeze_enemies && !end_game) {
		enemy_spawn_timer += deltaTimeSeconds;
		powerup_spawn_timer += deltaTimeSeconds;
	}

	/* The spawn threshold decreases per frame, from 2s to 0.5s */
	if (enemy_spawn_threshold > MIN_SPAWN_TIME && !freeze_enemies && !end_game) {
		enemy_spawn_threshold -= (deltaTimeSeconds / 100);
	}
	else if (enemy_spawn_threshold < MIN_SPAWN_TIME && !end_game) {
		enemy_spawn_threshold = MIN_SPAWN_TIME;
	}

	/* Enemies spawn every spawn_threshold seconds*/
	if (enemy_spawn_timer > enemy_spawn_threshold && !end_game) {
		spawnEnemies();
		enemy_spawn_timer = 0;
	}

	/* Powerups spawn every 10 seconds */
	if (powerup_spawn_timer > POWERUP_SPAWN_THRESHOLD && !freeze_enemies && !end_game) {
		powerup_spawn_timer = 0;
		spawnPowerup();
	}

	/* If freeze is over, reset the timer */
	if (freeze_timer > FREEZE_DURATION) {
		freeze_enemies = false;
		freeze_timer = 0;
	}
}

bool GameInstance::isEndGame(void) {
	return this->end_game;
}

void GameInstance::OnGameEnd(void) {
	this->end_game = true;
}

void GameInstance::spawnEnemies() {
	for (int i = 0; i < 3; i++) {


		float angle = (float)rand();
		glm::vec2 player_pos = player->getPosition();

		float radius = ENEMY_SPAWN_DISTANCE;

		float x = cos(angle) * radius;
		float y = sin(angle) * radius;


		Enemy* enemy;

		int lives_count = (rand() % 2) + 1;

		enemy = new Enemy(lives_count);
		enemy->setCenter(origin);

		enemy->setInitialPosition(player_pos + glm::vec2(x, y));

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