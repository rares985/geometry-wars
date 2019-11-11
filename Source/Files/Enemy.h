#pragma once

#ifndef ENEMY_H_
#define ENEMY_H_

#include "GameObject.h"



class Enemy : public GameObject {

public:
	Enemy(const std::string mesh_name, const glm::vec3& color, int initial_lives);
	~Enemy();

	void	HandleCollisionWith(Enemy& enemy) override;
	void	HandleCollisionWith(Projectile& projectile) override;
	void	HandleCollisionWith(Powerup& powerup) override;
	void	HandleCollisionWith(Player& player) override;

	void	UpdatePosition(float speed_cuantif);
	void	PerformShrink(float deltaTimeSeconds);
	int		getScorePoints(void) const;

private:
	void	TakeDamage(int damage);

};

#endif /* ENEMY_H_ */