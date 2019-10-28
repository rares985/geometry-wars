#pragma once

#ifndef FREEZE_POWERUP_H_
#define FREEZE_POWERUP_H_

#include "Powerup.h"
#include "constants.h"

class FreezePowerup : public Powerup {
public:
	FreezePowerup() : Powerup(FREEZE_POWERUP_MESH_NAME, darkcyan, FREEZE_POWERUP_SIZE) {};

};
#endif /* FREEZE_POWERUP_H_ */