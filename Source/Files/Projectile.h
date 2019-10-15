#pragma once

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "GameObject.h"

class Projectile : public GameObject {
public:
	Projectile();
	~Projectile();

	void updatePosition(float speed_cuantif);
private:

};

#endif /* PROJECTILE_H_ */
