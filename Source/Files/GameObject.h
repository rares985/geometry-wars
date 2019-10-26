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

		/* Attributes */
		float tx, ty;
		float scale;
		float rotation;

		float x_speed, y_speed;

		int initial_lives;
		int lives_left;

		bool visible;
		bool shrink;

		glm::vec3 center;

		std::string mesh_name;

		glm::mat3 model_matrix = glm::mat3();



		void setMoveDirection(glm::vec2 target);
		void setMeshName(std::string mesh_name) { this->mesh_name = mesh_name; };

		bool isVisible(void) { return this->visible; };

		void setColor(glm::vec3 color) { this->color = color; };
		void setSize(float size) { this->size = size; };
		void setCenter(glm::vec3 center) { this->center = center; };
		void setInitialPosition(float tx, float ty) { this->tx = tx; this->ty = ty; };

		std::string getMeshName() { return this->mesh_name; };

		void computeModelMatrix(glm::mat3 &vis_matrix);

		glm::vec3 getColor() { return this->color; };
		float getSize() { return this->size; };
		glm::vec3 getCenter() { return this->center; };
		glm::mat3 getModelMatrix() { return this->model_matrix; };
		int getLivesLeft() { return this->lives_left; };

		bool collidesWith(GameObject* other);

		virtual void collideWith(Player& player) = 0;
		virtual void collideWith(Projectile& projectile) = 0;
		virtual void collideWith(Enemy& enemy) = 0;
		virtual void collideWith(Powerup& powerup) = 0;

private:
	glm::vec3 color = glm::vec3();
	float size = 0.0f;
};

#endif /* GAME_OBJECT_H_ */
