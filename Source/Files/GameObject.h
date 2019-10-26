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
		float rotation;

		float x_speed, y_speed;

		int initial_lives;
		int lives_left;


		bool shrink;




		glm::mat3 model_matrix = glm::mat3();


		void moveTowards(glm::vec2 &target);

		void setSize(float size) { this->size = size; };
		void setScale(float scale) { this->scale = scale; };
		void setInitialPosition(float tx, float ty) { this->tx = tx; this->ty = ty; };
		void setInitialPosition(glm::vec2 pos) { this->tx = pos[0]; this->ty = pos[1]; };
		void setMeshName(std::string mesh_name) { this->mesh_name = mesh_name; };
		void setColor(glm::vec3 color) { this->color = color; };
		void setCenter(glm::vec3 center) { this->center = center; };
		void rotateTowards(glm::vec2 target) { this->rotation = atan((target.y - ty) / (target.x - tx)); };
		void makeInvisible(void) { this->visible = false; };


		bool isVisible(void) const { return this->visible; };

		void computeModelMatrix(glm::mat3 &vis_matrix);

		int getLivesLeft() const { return this->lives_left; };
		float getSize() const { return this->size; };
		float getScale() const { return this->scale; };
		std::string getMeshName() const { return this->mesh_name; };
		glm::vec2 getPosition() const { return glm::vec2(this->tx, this->ty); };
		glm::vec3 getColor() const { return this->color; };
		glm::vec3 getCenter() const { return this->center; };
		glm::mat3& getModelMatrix() { return this->model_matrix; };

		bool collidesWith(GameObject* other);

		virtual void collideWith(Player& player) = 0;
		virtual void collideWith(Projectile& projectile) = 0;
		virtual void collideWith(Enemy& enemy) = 0;
		virtual void collideWith(Powerup& powerup) = 0;

private:
	glm::vec3 color = glm::vec3();
	float size = 0.0f;

protected:
	std::string mesh_name;
	glm::vec3 center;
	bool visible;
	float tx, ty;
	float scale;

};

#endif /* GAME_OBJECT_H_ */
