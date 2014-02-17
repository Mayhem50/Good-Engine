#include "LoaderObj.h"

using namespace Good;

MeshPtr LoaderObj::load(const char* file)
{
	FILE* fic = NULL;
	fopen_s(&fic, file, "r");

	if (file == NULL)
		return nullptr;

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> positionList;
	std::vector<glm::vec2> uvList;
	std::vector<glm::vec3> normalList;

	int key = 0;

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
			key |= 0x01;
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf(fic, "%f %f", &uv.x, &uv.y);
			uvList.push_back(uv);
			key |= 0x02;
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf(fic, "%f %f %f", &normal.x, &normal.y, &normal.z);
			normalList.push_back(normal);
			key |= 0x04;
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = 0;

			if (key == 0x07)
				matches = fscanf(fic, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			else if (key == 0x03)
				matches = fscanf(fic, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
			else if (key == 0x05)
				matches = fscanf(fic, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
			else if (key == 0x01)
				matches = fscanf(fic, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);

			if ((key & 0x01))
			{
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
			}

			if ((key & 0x02))
			{
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
			}

			if ((key & 0x04))
			{
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
		else
		{
			char stupidBuffer[MAX_CHAR];
			fgets(stupidBuffer, MAX_CHAR, fic);
		}
	}

	MeshPtr mesh(new Mesh(NameTools::nameGenerator(), nullptr));

	for (unsigned int idx = 0; idx < vertexIndices.size(); ++idx)
	{
		Vertex vertex;

		if ((key & 0x01) == 1)
		{
			unsigned int vertexIndex = vertexIndices[idx];
			vertex.position = positionList[vertexIndex - 1];
		}
		if ((key & 0x02) == 1)
		{
			unsigned int uvIndex = uvIndices[idx];
			vertex.uv = uvList[uvIndex - 1];
		}
		if ((key & 0x04) == 1)
		{
			unsigned int normalIndex = normalIndices[idx];
			vertex.normal = normalList[normalIndex - 1];
		}

		mesh->addVertex(vertex);
	}

	return mesh;
}