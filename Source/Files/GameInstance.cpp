#include "GameInstance.h"
#include <cstdio>


GameInstance::GameInstance() {
	this->score = 0;
	this->end_game = false;
}

GameInstance::~GameInstance() {

}

void GameInstance::updateScore(int diff) {
	this->score += diff;

	printf("Score: %llu\n", this->score);
}

bool GameInstance::isEndGame(void) {
	return this->end_game;
}

void GameInstance::OnGameEnd(void) {
	this->end_game = true;
}