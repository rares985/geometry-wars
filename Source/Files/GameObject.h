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
		
		float			rotation;
		float			x_speed;
		float			y_speed;

		int				initial_lives;
		int				lives_left;

		bool			shrink;

		glm::mat3		model_matrix = glm::mat3();


		void			MoveTowards(const glm::vec2 &target);

		void			setSize(float size) { this->size = size; };
		void			setScale(float scale) { this->scale = scale; };
		void			setInitialPosition(float tx, float ty) { this->tx = tx; this->ty = ty; };
		void			setInitialPosition(glm::vec2 pos) { this->tx = pos.x; this->ty = pos.y; };
		void			setMeshName(std::string mesh_name) { this->mesh_name = mesh_name; };
		void			setColor(glm::vec3 color) { this->color = color; };
		void			setCenter(glm::vec3 center) { this->center = center; };
		void			RotateTowards(glm::vec2 target) { this->rotation = glm::atan(target.y - ty , target.x - tx); };
		void			MakeInvisible(void) { this->visible = false; };


		bool			IsVisible(void) const { return this->visible; };

		void			ComputeModelMatrix(const glm::mat3 &vis_matrix);

		int				getLivesLeft() const { return this->lives_left; };
		float			getSize() const { return this->size; };
		float			getScale() const { return this->scale; };
		std::string		getMeshName() const { return this->mesh_name; };
		glm::vec2		getPosition() const { return glm::vec2(this->tx, this->ty); };
		glm::vec3		getColor() const { return this->color; };
		glm::vec3		getCenter() const { return this->center; };
		glm::mat3&		getModelMatrix() { return this->model_matrix; };

		bool			CollidesWith(const GameObject &other);

		virtual void	HandleCollisionWith(Player&		player)		= 0;
		virtual void	HandleCollisionWith(Projectile& projectile) = 0;
		virtual void	HandleCollisionWith(Enemy&		enemy)		= 0;
		virtual void	HandleCollisionWith(Powerup&	powerup)	= 0;

private:




protected:
	GameObject(const std::string mesh_name, const glm::vec3 color, int size) : mesh_name(mesh_name), color(color), size(size) {};
	GameObject();
	~GameObject();

	bool				visible;

	float				tx;
	float				ty;
	float				scale;
	float				size;

	std::string			mesh_name;
	glm::vec3			center;
	glm::vec3			color;

};

#endif /* GAME_OBJECT_H_ */
