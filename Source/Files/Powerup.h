#pragma once

#ifndef POWERUP_H_
#define POWERUP_H_

#include "GameObject.h"

class Powerup : public GameObject {

public:

	Powerup(int type);
	Powerup(const std::string mesh_name, const glm::vec3 color, int size) : GameObject(mesh_name, color, size) {};
	~Powerup();

	void	HandleCollisionWith(Enemy& enemy) override;
	void	HandleCollisionWith(Projectile& projectile) override;
	void	HandleCollisionWith(Powerup& powerup) override;
	void	HandleCollisionWith(Player& player) override;

private:

};

#endif /* POWERUP_H_ */