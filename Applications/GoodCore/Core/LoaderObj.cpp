#include "LoaderObj.h"
#include "Model.h"

using namespace Good;

ModelPtr LoaderObj::load(const char* file)
{
	FILE* fic = NULL;
	fopen_s(&fic, file, "r");

	if (file == NULL)
		return nullptr;

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> positionList;
	std::vector<glm::vec2> uvList;
	std::vector<glm::vec3> normalList;

	while (1)
	{
		char lineHeader[MAX_CHAR];

		int res = fscanf_s(fic, "%s", lineHeader);

		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 position;
			fscanf_s(fic, "%f %f %f", &position.x, &position.y, &position.z);
			positionList.push_back(position);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf_s(fic, "%f %f", &uv.x, &uv.y);
			uvList.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf_s(fic, "%f %f %f", &normal.x, &normal.y, &normal.z);
			normalList.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(fic, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			
			if (matches != 9)
				return nullptr;

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);

			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);

			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else
		{
			char stupidBuffer[MAX_CHAR];
			fgets(stupidBuffer, MAX_CHAR, fic);
		}
	}

	std::vector<VertexPtr> vertexList;
	for (unsigned int idx = 0; idx < vertexIndices.size(); ++idx)
	{
		unsigned int vertexIndex = vertexIndices[idx];
		unsigned int uvIndex = uvIndices[idx];
		unsigned int normalIndex = normalIndices[idx];

		VertexPtr vertex(new Vertex);
		vertex->position = positionList[vertexIndex - 1];
		vertex->normal = normalList[normalIndex - 1];
		vertex->uv = uvList[uvIndex - 1];
		vertex->color = glm::vec3(0.0);

		vertexList.push_back(vertex);
	}

	return ModelPtr(new Model(vertexList));
}