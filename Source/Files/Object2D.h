#pragma once

#ifndef OBJECT_2D_H_
#define OBJECT_2D_H_

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{
	Mesh* GetShipMesh(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill);
	Mesh* GetProjectileMesh(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill);
	Mesh* GetLifeIndicatorMesh(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill);
	Mesh* GetLifePowerupMesh(std::string name, glm::vec3 center, float size, glm::vec3 color, bool fill);
	Mesh* GetFreezePowerupMesh(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill);

}

#endif /* OBJECT_2D_H_ */

