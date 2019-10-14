#pragma once

#ifndef POWERUP_H_
#define POWERUP_H_

#include "GameObject.h"

class Powerup : public GameObject {
public:
	Powerup(int type);
	~Powerup();

private:
	int type;
};

#endif /* POWERUP_H_ */