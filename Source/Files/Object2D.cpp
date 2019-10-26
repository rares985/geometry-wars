#include "Object2D.h"

#include <Core/Engine.h>

Mesh* CreateMesh(std::string name, std::vector <VertexFormat> &vertices, std::vector<unsigned short> &indices, bool fill) {
	Mesh* new_mesh = new Mesh(name);

	if (!fill) {
		new_mesh->SetDrawMode(GL_LINE_LOOP);
	}
	new_mesh->InitFromData(vertices, indices);

	return new_mesh;
}

Mesh* Object2D::GetShipMesh(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill) {
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center + glm::vec3(-radius,-radius,0),color),
		VertexFormat(center + glm::vec3(-radius,radius,0),color),
		VertexFormat(center, color),
		VertexFormat(center + glm::vec3(radius,radius,0),color),
		VertexFormat(center + glm::vec3(radius,-radius,0), color)
	};

	std::vector<unsigned short> indices = { 1,3,2,2,0,4 };

	return CreateMesh(name, vertices, indices, fill);
}

Mesh* Object2D::GetProjectileMesh(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill) {
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center, color),
		VertexFormat(center + glm::vec3(-length, length / 4		,0),	color),
		VertexFormat(center + glm::vec3(length,  length / 4,	0),		color),
		VertexFormat(center + glm::vec3(length,  -length / 4,	0),		color),
		VertexFormat(center + glm::vec3(-length, -length / 4,	0),		color)
	};

	std::vector<unsigned short> indices = { 0,1,2,2,0,3,3,0,4,4,0,1 };


	return CreateMesh(name, vertices, indices, fill);
}

Mesh* Object2D::GetLifeIndicatorMesh(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill) {
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center, color),
		VertexFormat(center + glm::vec3(-length / 4,	length,	0),	color),
		VertexFormat(center + glm::vec3(length / 4,		length,	0),	color),
		VertexFormat(center + glm::vec3(length / 4,		-length,	0) ,color),
		VertexFormat(center + glm::vec3(-length / 4,	-length,	0) ,color)
	};


	std::vector<unsigned short> indices = { 0,1,2,2,0,3,3,0,4,4,0,1 };

	return CreateMesh(name, vertices, indices, fill);
}

Mesh* Object2D::GetLifePowerupMesh(std::string name, glm::vec3 center, float size, glm::vec3 color, bool fill) {
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
	return CreateMesh(name, vertices, indices, fill);
}

Mesh* Object2D::GetFreezePowerupMesh(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill) {
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center, color),
		VertexFormat(center + glm::vec3(length,length ,0) ,color),
		VertexFormat(center + glm::vec3(length ,-length ,0) ,color),
		VertexFormat(center + glm::vec3(-length ,-length ,0) ,color),
		VertexFormat(center + glm::vec3(-length ,length ,0) ,color)
	};

	std::vector<unsigned short> indices = { 0,1,2,2,0,3,3,0,4,4,0,1 };

	return CreateMesh(name, vertices, indices, fill);
}