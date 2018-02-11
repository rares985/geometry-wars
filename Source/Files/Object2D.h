#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateShip(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill);
	Mesh* CreateProjectile(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill);
	Mesh* CreateLifeMesh(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill);
	Mesh* CreateLifePowerup(std::string name, glm::vec3 center, float size, glm::vec3 color, bool fill);
	Mesh* CreateFreezePowerup(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill);

}

