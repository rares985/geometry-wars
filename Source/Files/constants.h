#pragma once

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "Core/Engine.h"

/* various mesh sizes */
#define PLAYER_SIZE 0.4f
#define PROJECTILE_SIZE 0.1f
#define DEFAULT_ENEMY_SIZE 0.3f
#define SHRINKED_ENEMY_SIZE 0.3f
#define LIVES_SIZE 0.2f
#define LIFE_POWERUP_SIZE 0.2f
#define FREEZE_POWERUP_SIZE 0.15f

#define ENEMY_SPAWN_DISTANCE 6.0f


/* various durations*/
#define INITIAL_SPAWN_TIME 2.0f
#define MIN_SPAWN_TIME 0.5f
#define SHRINK_ANIMATION_DURATION 0.25f
#define POWERUP_SPAWN_THRESHOLD 10.0f
#define FREEZE_DURATION 2.0f

#define LOGIC_WINDOW_HEIGHT 9
#define LOGIC_WINDOW_WIDTH 16


/* rgb colour codes */
glm::vec3 black = glm::vec3(0, 0, 0);
glm::vec3 white = glm::vec3(1, 1, 1);
glm::vec3 gold = glm::vec3(1, 0.843137, 0);
glm::vec3 yellow = glm::vec3(1, 1, 0);
glm::vec3 deepskyblue = glm::vec3(0, 0.74902, 1);
glm::vec3 red = glm::vec3(1, 0, 0);
glm::vec3 firebrick = glm::vec3(0.698039, 0.133333, 0.133333);
glm::vec3 origin = glm::vec3(0, 0, 0);
glm::vec3 green = glm::vec3(0, 1, 0);
glm::vec3 aquamarine = glm::vec3 (0.498039f ,1.0f, 0.831373f);
glm::vec3 darkcyan = glm::vec3(0, 0.545098, 0.545098);
glm::vec3 forestgreen = glm::vec3(0.133333, 0.545098, 0.133333);
glm::vec3 ivory = glm::vec3(1, 1, 0.941176);

#endif