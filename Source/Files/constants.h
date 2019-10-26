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
#define ENEMIES_SPAWNED_PER_ROUND 3


/* various durations*/
#define INITIAL_SPAWN_TIME 2.0f
#define MIN_SPAWN_TIME 0.5f
#define SHRINK_ANIMATION_DURATION 0.25f
#define POWERUP_SPAWN_THRESHOLD 10.0f
#define FREEZE_DURATION 2.0f

/* Size of window in PX */
#define WINDOW_WIDTH_PX		1280
#define WINDOW_HEIGHT_PX	720

/* Size of Logic space of window */
#define LOGIC_WINDOW_HEIGHT 9
#define LOGIC_WINDOW_WIDTH 16

/* Scaling factor... */
#define LOGIC_SCALE_FACTOR 80 /* WINDOW_WIDTH / LOGIC_WIDTH */

/* rgb colour codes */
#define black  glm::vec3(0, 0, 0)
#define white  glm::vec3(1, 1, 1)
#define gold  glm::vec3(1, 0.843137, 0)
#define yellow  glm::vec3(1, 1, 0)
#define deepskyblue  glm::vec3(0, 0.74902, 1)
#define red  glm::vec3(1, 0, 0)
#define firebrick  glm::vec3(0.698039, 0.133333, 0.133333)
#define origin  glm::vec3(0, 0, 0)
#define green  glm::vec3(0, 1, 0)
#define aquamarine  glm::vec3 (0.498039f ,1.0f, 0.831373f)
#define darkcyan  glm::vec3(0, 0.545098, 0.545098)
#define forestgreen  glm::vec3(0.133333, 0.545098, 0.133333)
#define ivory  glm::vec3(1, 1, 0.941176)

#endif