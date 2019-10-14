#pragma once

#ifndef GAME_INSTANCE_H_
#define GAME_INSTANCE_H_

#include <chrono>

class GameInstance {
public:
	GameInstance();
	~GameInstance();

	void updateScore(int diff);
	bool isEndGame(void);

	void OnGameEnd(void);

private:
	long long int score;
	bool end_game;


};


#endif /* GAME_INSTANCE_H_ */
