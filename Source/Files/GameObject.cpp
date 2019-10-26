#include "GameObject.h"
#include "Transform2D.h"

GameObject::GameObject() {
	this->mesh_name = "";
	this->center = glm::vec3();
	this->size = 0.0f;
	this->color = glm::vec3();
	this->rotation = 0.0f;
	this->scale = 1.0f;
	model_matrix = glm::mat3(1);
	tx = ty = 0;
	x_speed = y_speed = 0;
	visible = true;
	shrink = false;
}

GameObject::~GameObject()
{
	// de-allocate
}

bool GameObject::collidesWith(GameObject* other) {
	float xdist = tx - other->tx;
	float ydist = ty - other->ty;
	float abs_dist = xdist * xdist + ydist * ydist;
	float radii_dist = (getSize() + other->getSize()) * (getSize() + other->getSize());
	return (abs_dist <= radii_dist);
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

void GameObject::computeModelMatrix(glm::mat3 &vis_matrix)
{
	this->model_matrix = vis_matrix;
	this->model_matrix *= Transform2D::Translate(tx, ty);
	this->model_matrix *= Transform2D::Rotate(rotation);
	this->model_matrix *= Transform2D::Scale(this->scale, this->scale);
}
