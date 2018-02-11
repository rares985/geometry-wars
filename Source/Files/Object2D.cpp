#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateShip(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill) {
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center + glm::vec3(-radius,-radius,0),color),
		VertexFormat(center + glm::vec3(-radius,radius,0),color),
		VertexFormat(center, color),
		VertexFormat(center + glm::vec3(radius,radius,0),color),
		VertexFormat(center + glm::vec3(radius,-radius,0), color)
	};

	Mesh* ship = new Mesh(name);
	std::vector<unsigned short> indices = { 1,3,2,2,0,4 };

	if (!fill) {
		ship->SetDrawMode(GL_LINE_LOOP);
	}
	else {

	}
	ship->InitFromData(vertices, indices);
	return ship;
}

Mesh* Object2D::CreateProjectile(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill) {
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center, color),
		VertexFormat(center + glm::vec3(-length  ,length /4 ,0) ,color),
		VertexFormat(center + glm::vec3(length ,length/4,0) ,color),
		VertexFormat(center + glm::vec3(length ,-length/4,0) ,color),
		VertexFormat(center + glm::vec3(-length ,-length/4,0) ,color)
	};


	Mesh* projectile = new Mesh(name);
	std::vector<unsigned short> indices = { 0,1,2,2,0,3,3,0,4,4,0,1 };

	if (!fill) {
		projectile->SetDrawMode(GL_LINE_LOOP);
	}
	else {

	}
	projectile->InitFromData(vertices, indices);
	return projectile;
}

Mesh* Object2D::CreateLifeMesh(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill) {
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center, color),
		VertexFormat(center + glm::vec3(-length / 4  ,length ,0) ,color),
		VertexFormat(center + glm::vec3(length / 4 ,length,0) ,color),
		VertexFormat(center + glm::vec3(length / 4 ,-length,0) ,color),
		VertexFormat(center + glm::vec3(-length / 4 ,-length,0) ,color)
	};


	Mesh* projectile = new Mesh(name);
	std::vector<unsigned short> indices = { 0,1,2,2,0,3,3,0,4,4,0,1 };

	if (!fill) {
		projectile->SetDrawMode(GL_LINE_LOOP);
	}
	else {

	}
	projectile->InitFromData(vertices, indices);
	return projectile;
}

Mesh* Object2D::CreateLifePowerup(std::string name, glm::vec3 center, float size, glm::vec3 color, bool fill) {
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center,color),
		VertexFormat(center + glm::vec3(-size / 3,size / 3,0),color),
		VertexFormat(center + glm::vec3(-size / 3,size,0),color),
		VertexFormat(center + glm::vec3(size / 3,size,0),color),
		VertexFormat(center + glm::vec3(size / 3,size / 3,0),color),
		VertexFormat(center + glm::vec3(size,size / 3,0),color),
		VertexFormat(center + glm::vec3(size,-size / 3,0),color),
		VertexFormat(center + glm::vec3(size / 3,-size / 3,0),color),
		VertexFormat(center + glm::vec3(size / 3,-size,0),color),
		VertexFormat(center + glm::vec3(-size / 3,-size,0),color),
		VertexFormat(center + glm::vec3(-size / 3,-size / 3,0),color),
		VertexFormat(center + glm::vec3(-size,-size / 3,0),color),
		VertexFormat(center + glm::vec3(-size,size / 3,0),color)
	};
	Mesh* m = new Mesh(name);
	std::vector<unsigned short> indices = 
	{	0, 1, 4,
		4, 1, 2,
		2, 3, 4,
		4, 5, 6,
		6, 7, 4,
		4, 7, 0,
		0, 7, 10,
		10, 7, 8,
		8, 9, 10,
		10, 11, 12,
		12,1,10,
		10,1,0 };
	m->InitFromData(vertices, indices);
	return m;
}

Mesh* Object2D::CreateFreezePowerup(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill) {
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center, color),
		VertexFormat(center + glm::vec3(length,length ,0) ,color),
		VertexFormat(center + glm::vec3(length ,-length ,0) ,color),
		VertexFormat(center + glm::vec3(-length ,-length ,0) ,color),
		VertexFormat(center + glm::vec3(-length ,length ,0) ,color)
	};


	Mesh* projectile = new Mesh(name);
	std::vector<unsigned short> indices = { 0,1,2,2,0,3,3,0,4,4,0,1 };

	if (!fill) {
		projectile->SetDrawMode(GL_LINE_LOOP);
	}
	else {

	}
	projectile->InitFromData(vertices, indices);
	return projectile;
}