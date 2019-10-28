#pragma once


#ifndef LIFE_POWERUP_H_
#define LIFE_POWERUP_H_

#include "Powerup.h"
#include "constants.h"

class LifePowerup : public Powerup
{

public:
	LifePowerup() : Powerup(LIFE_POWERUP_MESH_NAME, forestgreen, LIFE_POWERUP_SIZE) {};

};

#endif /* LIFE_POWERUP_H_ */