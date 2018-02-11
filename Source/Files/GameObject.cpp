#include "GameObject.h"

GameObject::GameObject(Mesh* m, std::string mesh_name, glm::vec3 center, float size, glm::vec3 color) {
	mesh = m;
	this->mesh_name = mesh_name;
	this->center = center;
	this->size = size;
	color = color;
	rotation = 0;
	scale = 1;
	model_matrix = glm::mat3(1);
	tx = ty = 0;
	x_speed = y_speed = 0;
	should_render = true;
	shrink = false;
}

void GameObject::setMoveDirection(glm::vec2 target) {
	float dx = target.x - tx;
	float dy = target.y - ty;
	float dist = sqrt(dx*dx + dy*dy);
	float steps = dist / 0.5f;
	float xspeed = dx / steps;
	float yspeed = dy / steps;

	x_speed = xspeed;
	y_speed = yspeed;
	rotation = atan(dy / dx);
}