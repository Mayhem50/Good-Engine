#include "LoaderObj.h"

using namespace Good;

MeshPtr LoaderObj::load(const char* file)
{
	FILE* fic = NULL;
	fopen_s(&fic, file, "r");

	if (file == NULL)
		return nullptr;

	std::vector<unsigned int> vertexIndices;
	std::vector<glm::vec3> positionList;

	MeshPtr mesh(new Mesh(NameTools::nameGenerator(), nullptr));

	while (1)
	{
		char lineHeader[MAX_CHAR];

		int res = fscanf(fic, "%s", lineHeader);

		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 position;
			fscanf(fic, "%f %f %f", &position.x, &position.y, &position.z);
			positionList.push_back(position);
			mesh->addVertex(position);
		}
		
		else if (strcmp(lineHeader, "f") == 0)
		{
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = 0;

			matches = fscanf(fic, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
			
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
		}
		else
		{
			char stupidBuffer[MAX_CHAR];
			fgets(stupidBuffer, MAX_CHAR, fic);
		}
	}
	
	for (unsigned int idx = 0; idx < vertexIndices.size();)
	{
		Vertex v1, v2, v3;
		unsigned int i1, i2, i3;

		i1 = vertexIndices[idx] - 1;
		++idx;
		i2 = vertexIndices[idx] - 1;
		++idx;
		i3 = vertexIndices[idx] - 1;
		++idx;

		v1.position = positionList[i1];
		v1.indice = i1; 
		v2.position = positionList[i2];
		v2.indice = i2;
		v3.position = positionList[i3];
		v3.indice = i3;

		mesh->createTriangles(i1, i2, i3);
	}

	return mesh;
}