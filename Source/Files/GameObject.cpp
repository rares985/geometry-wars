#include "GameObject.h"
#include "Transform2D.h"

GameObject::GameObject() {
	mesh = nullptr;
	this->mesh_name = "";
	this->center = glm::vec3();
	this->size = 0.0f;
	this->color = glm::vec3();
	this->rotation = 0.0f;
	this->scale = 1.0f;
	model_matrix = glm::mat3(1);
	tx = ty = 0;
	x_speed = y_speed = 0;
	should_render = true;
	shrink = false;
}

GameObject::~GameObject()
{
	// de-allocate
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

void GameObject::setMeshInfo(Mesh* m, std::string mesh_name)
{
	this->mesh = m;
	this->mesh_name = mesh_name;
}

void GameObject::setColor(glm::vec3 color)
{
	this->color = color;
}

void GameObject::setSize(float size)
{
	this->size = size;
}

void GameObject::setCenter(glm::vec3 center)
{
	this->center = center;
}

void GameObject::setInitialPosition(float tx, float ty)
{
	this->tx = tx;
	this->ty = ty;
}

void GameObject::computeModelMatrix(glm::mat3 &vis_matrix)
{
	this->model_matrix = vis_matrix;
	this->model_matrix *= Transform2D::Translate(tx, ty);
	this->model_matrix *= Transform2D::Rotate(rotation);
	this->model_matrix *= Transform2D::Scale(this->scale, this->scale);
}

glm::vec3 GameObject::getColor()
{
	return this->color;
}

float GameObject::getSize()
{
	return this->size;
}

glm::vec3 GameObject::getCenter()
{
	return this->center;
}

glm::mat3 GameObject::getModelMatrix()
{
	return this->model_matrix;
}
