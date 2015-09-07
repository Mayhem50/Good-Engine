#include "LoaderObj.h"

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp\scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <sstream>

#include <windows.h>
#include <process.h>

#include <openssl\sha.h>

namespace Good
{
#define SHA_KEY_LENGH 65

	std::vector<std::string> split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
		return elems;
	}
	void sha256_hash_string(unsigned char hash[SHA256_DIGEST_LENGTH], char outputBuffer[65]);

	int calc_sha256(const char* path, char output[SHA_KEY_LENGH])
	{
		FILE* file = fopen(path, "rb");
		if (!file) return -1;

		unsigned char hash[SHA256_DIGEST_LENGTH];
		SHA256_CTX sha256;
		SHA256_Init(&sha256);
		const unsigned int bufSize = 0xffffffff;
		char* buffer = new char[bufSize];
		int bytesRead = 0;
		if (!buffer) return -1;
		while ((bytesRead = fread(buffer, 1, bufSize, file)))
		{
			SHA256_Update(&sha256, buffer, bytesRead);
		}
		SHA256_Final(hash, &sha256);

		sha256_hash_string(hash, output);
		fclose(file);
		delete[] buffer;
		return 0;
	}

	void sha256_hash_string(unsigned char hash[SHA256_DIGEST_LENGTH], char outputBuffer[SHA_KEY_LENGH])
	{
		int i = 0;

		for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
		{
			sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
		}

		outputBuffer[SHA_KEY_LENGH - 1] = 0;
	}

	MeshPtr GeometryLoader::load(const char* file)
	{
		FILE* fic = NULL;
		fopen_s(&fic, file, "r");

		if (file == NULL)
			return nullptr;

		char calc_hash[SHA_KEY_LENGH];
		calc_sha256(file, calc_hash);
		std::cout << "File : "<< file << " \tSHA1: "  << calc_hash << std::endl;

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