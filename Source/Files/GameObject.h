#pragma once

#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include<Core/Engine.h>

class Player;
class Projectile;
class Powerup;
class Enemy;

class GameObject {

	public:
		
		GameObject();
		~GameObject();

		void setMoveDirection(glm::vec2 target);
		void setMeshInfo(std::string mesh_name);

		void setColor(glm::vec3 color);
		void setSize(float size);
		void setCenter(glm::vec3 center);
		std::string getMeshName();

		void setInitialPosition(float tx, float ty);
		void computeModelMatrix(glm::mat3 &vis_matrix);

		glm::vec3 getColor();
		float getSize();
		glm::vec3 getCenter();
		glm::mat3 getModelMatrix();

		bool collidesWith(GameObject* other);

		virtual void collideWith(Player& player) = 0;
		virtual void collideWith(Projectile& projectile) = 0;
		virtual void collideWith(Enemy& enemy) = 0;
		virtual void collideWith(Powerup& powerup) = 0;

		glm::vec3 center;
		
		std::string mesh_name;



		float tx, ty;
		float scale;
		float rotation;

		float x_speed, y_speed;
		
		int initial_lives;
		int lives_left;

		bool should_render;
		bool shrink;
		glm::mat3 model_matrix = glm::mat3();

private:
	glm::vec3 color = glm::vec3();
	float size = 0.0f;
};

#endif /* GAME_OBJECT_H_ */
