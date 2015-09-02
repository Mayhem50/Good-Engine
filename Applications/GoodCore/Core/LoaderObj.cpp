#include "LoaderObj.h"

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp\scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <sstream>

#include <windows.h>
#include <process.h>

namespace Good
{
	HANDLE mutex;
	const unsigned int MAX_THREAD = 8;

	struct FaceTrunck
	{
		unsigned int start;
		unsigned int end;
		aiMesh* iMesh;
		MeshPtr mesh;
		unsigned int threadID;
	};

	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}


	std::vector<std::string> split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		split(s, delim, elems);
		return elems;
	}

	void batchFaces(void* data)
	{
		WaitForSingleObject(mutex, INFINITE);
		FaceTrunck* trunk = static_cast<FaceTrunck*>(data);
		ReleaseMutex(mutex);

		for (unsigned int idx = trunk->start; idx < trunk->end; ++idx)
		{
			WaitForSingleObject(mutex, INFINITE);

			auto iMesh = trunk->iMesh;
			auto face = iMesh->mFaces[idx];
			std::cout << "Thread: " << trunk->threadID << " batch face : " << idx << std::endl;

			Vertex vertex[3];

			for (int jdx = 0; jdx < 3; ++jdx)
			{
				memcpy(&vertex[jdx].position, &(iMesh->mVertices[face.mIndices[jdx]]), sizeof(glm::vec3));
				memcpy(&vertex[jdx].normal, &(iMesh->mNormals[face.mIndices[jdx]]), sizeof(glm::vec3));
				vertex[jdx].indice = face.mIndices[jdx];

				vertex[jdx].indice = face.mIndices[jdx];
			}

			trunk->mesh->createTriangles(vertex[0], vertex[1], vertex[2]);
			ReleaseMutex(mutex);
		}

		return;
	}


	MeshPtr GeometryLoader::load(const char* file)
	{
		FILE* fic = NULL;
		fopen_s(&fic, file, "r");

		if (file == NULL)
			return nullptr;

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uvs;

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
				positions.push_back(position);
			}

			else if (strcmp(lineHeader, "vn") == 0)
			{
				glm::vec3 normal;
				fscanf(fic, "%f %f %f", &normal.x, &normal.y, &normal.z);
				normals.push_back(normal);
			}

			else if (strcmp(lineHeader, "vt") == 0)
			{
				glm::vec2 uv;
				fscanf(fic, "%f %f", &uv.x, &uv.y);
				uvs.push_back(uv);
			}

			else if (strcmp(lineHeader, "f") == 0)
			{
				char** str = new char* [3];

				for (int idx = 0; idx < 3; ++idx)
					str[idx] = new char[MAX_CHAR];

				int matches = 0;

				matches = fscanf(fic, "%s %s %s\n", str[0], str[1], str[2]);

				Vertex v[3];

				for (int idx = 0; idx < 3; ++idx)
				{
					std::vector<std::string> strs = split(str[idx], '/');

					v[idx].indice = std::stoi(strs[0]);

					v[idx].position = positions[std::stoi(strs[0]) - 1];

					if (!strs[1].empty())
						v[idx].uv = uvs[std::stoi(strs[1]) - 1];

					if (!strs[2].empty())
						v[idx].normal = normals[std::stoi(strs[2]) - 1];

					mesh->addVertex(v[idx]);
				}

				mesh->createTriangles(v[0].indice, v[1].indice, v[2].indice);
			}
			else
			{
				char stupidBuffer[MAX_CHAR];
				fgets(stupidBuffer, MAX_CHAR, fic);
			}
		}

		/*Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(file, 0);
		std::cout << "Finish Assimp Import" << std::endl;
		auto iMesh = scene->mMeshes[0];*/

		/*unsigned int nbfacesPerTrunk = iMesh->mNumFaces / MAX_THREAD;

		FaceTrunck trunk[MAX_THREAD];
		for (int idx = 0; idx < MAX_THREAD; ++idx)
		{
			trunk[idx].iMesh = iMesh;
			trunk[idx].start = nbfacesPerTrunk * idx;
			trunk[idx].end = trunk[idx].start + nbfacesPerTrunk;

			if (idx == MAX_THREAD - 1)
			{
				trunk[idx].end = iMesh->mNumFaces;
			}

			trunk[idx].mesh = mesh;
			trunk[idx].threadID = idx;
		}

		mutex = CreateMutex(NULL, FALSE, NULL);

		HANDLE threadHandle[MAX_THREAD];

		for (int idx = 0; idx < MAX_THREAD; ++idx)
		{
			threadHandle[idx] = (HANDLE)_beginthread(&batchFaces, 0, &trunk[idx]);
		}

		WaitForMultipleObjects(MAX_THREAD, threadHandle, true, INFINITE);*/

		//VerticesList vertices;
		//vertices.resize(iMesh->mNumVertices);
		//auto verticesPointer = vertices.data();

		//std::cout << "Begin conversion" << std::endl;
		//for (unsigned int idx = 0; idx < iMesh->mNumFaces; ++idx)
		//{
		//auto face = iMesh->mFaces[idx];
		//
		////std::cout << idx << std::endl;

		//for (int jdx = 0; jdx < 3; ++jdx)
		//{
		//	memcpy(&vertices[face.mIndices[jdx]].position, &(iMesh->mVertices[face.mIndices[jdx]]), sizeof(glm::vec3));
		//	memcpy(&vertices[face.mIndices[jdx]].normal, &(iMesh->mNormals[face.mIndices[jdx]]), sizeof(glm::vec3));
		//	vertices[face.mIndices[jdx]].indice = face.mIndices[jdx];
		//}

		//mesh->createTriangles(vertices[face.mIndices[0]], vertices[face.mIndices[1]], vertices[face.mIndices[2]]);
		//}
		//std::cout << "End conversion" << std::endl;

		return mesh;
	}
}