#include "GameObject.h"
#include "Transform2D.h"
#include "constants.h"

GameObject::GameObject() {
	this->mesh_name = "";
	this->center = origin;
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

bool GameObject::collidesWith(const GameObject* other) {
	bool objects_collide = false;

	if (this->isVisible() && other->isVisible()) {

		glm::vec2 dist = getPosition() - other->getPosition();

		float abs_dist = glm::dot(dist, dist);
		
		float radii_dist = (getSize() + other->getSize()) * (getSize() + other->getSize());

		objects_collide = (abs_dist <= radii_dist);
	}

	return objects_collide;
}

void GameObject::moveTowards(const glm::vec2 &target) {
	
	float dx = target.x - tx;
	float dy = target.y - ty;

	float steps = glm::distance(target, getPosition()) / 0.5f;

	x_speed = dx / steps;
	y_speed = dy / steps;

	rotation = glm::atan(dy, dx);
}

void GameObject::computeModelMatrix(const glm::mat3 &vis_matrix)
{
	this->model_matrix = vis_matrix;
	this->model_matrix *= Transform2D::Translate(tx, ty);
	this->model_matrix *= Transform2D::Rotate(rotation);
	this->model_matrix *= Transform2D::Scale(this->scale, this->scale);
}
