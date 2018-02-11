#pragma once

#include<Core/Engine.h>

class GameObject {

	public:
		
		GameObject(Mesh* m, std::string mesh_name, glm::vec3 center, float size, glm::vec3 color);

		void setMoveDirection(glm::vec2 target);


		Mesh* mesh;
		
		
		glm::mat3 model_matrix;
		std::string mesh_name;

		float tx, ty;
		float scale;
		float rotation;
		float size;

		glm::vec3 color;
		glm::vec3 center;

		float x_speed, y_speed;
		
		int initial_lives;
		int lives_left;

		bool should_render;
		bool shrink;
};
