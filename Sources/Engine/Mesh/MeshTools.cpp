#include "MeshTools.h"

#include "../Core/Constants.h"

namespace Good
{
	MeshPtr MeshTools::createSphere(int meridians, int parallels)
	{
		int vertices = parallels * meridians + 2;
				
		MeshPtr mesh(new Mesh("Sphere", nullptr));

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		
		initializePositionsAndNormalsList(positions, normals, vertices);

		// South Pole
		positions[0] = glm::vec3(0.0, -1.0, 0.0);
		normals[0] = glm::vec3(0.0, -1.0, 0.0);

		for(int par = 0; par < parallels; ++par)
		{
			for(int mer = 0; mer < meridians; ++mer)
			{
				positions[(1 + par * meridians + mer)].x = cos(MATH_PI * (par + 1) / (parallels + 1) - MATH_PI_2) * sin(2.0f * MATH_PI * mer / (meridians));
				positions[(1 + par * meridians + mer)].y = sin(MATH_PI * (par + 1)/(parallels + 1) - MATH_PI_2);
				positions[(1 + par * meridians + mer)].z = cos(MATH_PI * (par + 1)/(parallels + 1) - MATH_PI_2) * cos(2 * MATH_PI * mer/(meridians));

				
				normals[(1 + par*meridians + mer)].x = cos(MATH_PI * (par + 1)/(parallels + 1) - MATH_PI_2) * sin(2 * MATH_PI * mer/(meridians));
				normals[(1 + par*meridians + mer)].y = sin(MATH_PI * (par + 1)/(parallels + 1) - MATH_PI_2);
				normals[(1 + par*meridians + mer)].z = cos(MATH_PI * (par + 1)/(parallels + 1) - MATH_PI_2) * cos(2 * MATH_PI * mer/(meridians));
			}
		}

		// North Pole
		positions[vertices - 1] = glm::vec3(0.0, 1.0, 0.0);
		normals[vertices - 1] = glm::vec3(0.0, 1.0, 0.0);
		
		for(int idx = 0; idx < vertices; ++idx)
		{
			Vertex vertex;
			vertex.position = positions[idx];
			vertex.normal = normals[idx];

			mesh->addVertex(vertex);
		}

		int idx = 0;

		for(int mer = 0; mer < meridians; ++mer)
		{
			int v1, v2, v3;
			v1 = 0;
			v2 = 1 + (mer + 1) % meridians;
			v3 = 1 + mer;

			mesh->createTriangles(v1, v2, v3);
		}

		for(int par = 0; par < parallels; ++par)
		{
			for(int mer = 0; mer < meridians; ++mer)
			{
				int v1, v2, v3;

				v1 = 1 + mer + par * meridians;
				v2 = 1 + (mer + 1) % meridians + par * meridians;
				v3 = 1 + (mer + 1) % meridians + (par + 1) * meridians;

				mesh->createTriangles(v1, v2, v3);

				int v4, v5, v6;
				
				v4 = 1 + mer + par * meridians;
				v5 = 1 + (mer + 1) % meridians + (par + 1) * meridians;
				v6 = 1 + mer + (par + 1) * meridians ;

				mesh->createTriangles(v4, v5, v6);
			}
		}

		for(int mer = 0; mer < meridians; ++mer)
		{
			int v1, v2, v3;

			v1 = 1 + meridians * (parallels - 1) + mer;
			v2 = 1 + meridians * (parallels - 1) + (mer + 1) % meridians;
			v3 = vertices - 1;

			mesh->createTriangles(v1, v2, v3);
		}

		mesh->init();
		return mesh;
	}

	MeshPtr MeshTools::createPlane(int dX, int dY)
	{
		int vertices = (dX + 1) * (dY + 1);

		MeshPtr mesh(new Mesh("Plane", nullptr));

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;

		initializePositionsAndNormalsList(positions, normals, vertices);

		for(int vertical = 0; vertical <= dY; ++vertical)
		{
			for(int horizontal = 0; horizontal <= dX; ++horizontal)
			{
				positions[(horizontal + vertical * (dX + 1))].x = (horizontal - dX / 2.0) / (dX / 2.0);
				positions[(horizontal + vertical * (dX + 1))].y = (vertical - dY / 2.0) / (dY / 2.0);
				positions[(horizontal + vertical * (dX + 1))].z = 0.0;

				normals[(horizontal + vertical * (dX + 1))] = glm::vec3(0.0, 0.0, 1.0);
			}
		}

		for(int idx = 0; idx < vertices; ++idx)
		{
			Vertex vertex;
			vertex.position = positions[idx];
			vertex.normal = normals[idx];

			mesh->addVertex(vertex);
		}

		int idx = 0;

		for(int vertical = 0; vertical < dY; ++vertical)
		{
			for(int horizontal = 0; horizontal < dX; ++horizontal)
			{
				int v1, v2, v3;
				v1 = horizontal + vertical * (dX + 1);
				v2 = (horizontal + 1) + vertical * (dX + 1);
				v3 = horizontal + (vertical + 1) * (dX + 1);

				mesh->createTriangles(v1, v2, v3);
				
				int v4, v5, v6;
				v4 = horizontal + (vertical + 1) * (dX + 1);
				v5 = (horizontal + 1) + vertical * (dX + 1);
				v6 = (horizontal + 1) + (vertical + 1) * (dX + 1);

				mesh->createTriangles(v4, v5, v6);
			}
		}

		mesh->init();

		return mesh;
	}

	void MeshTools::initializePositionsAndNormalsList(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, int vertices)
	{
		positions.reserve(vertices);
		normals.reserve(vertices);

		for(int idx = 0; idx < vertices; ++idx)
		{
			positions.push_back(glm::vec3(0.0));
			normals.push_back(glm::vec3(0.0));
		}
	}
}