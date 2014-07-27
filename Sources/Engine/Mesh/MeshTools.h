#pragma once

#include "Mesh.h"

#include <vector>
#include <glm/glm.hpp>

namespace Good
{
	namespace MeshTools
	{
		MeshPtr createSphere(int meridians, int parallels);
		MeshPtr createPlane(int dX, int dY);

		void  initializePositionsAndNormalsList(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, int vertices);
	}
}
