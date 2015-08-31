#include "LoaderObj.h"

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp\scene.h>
#include <assimp/postprocess.h>

using namespace Good;

MeshPtr LoaderObj::load(const char* file)
{
	MeshPtr mesh(new Mesh(NameTools::nameGenerator(), nullptr));

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(file, aiProcess_GenNormals | aiProcess_CalcTangentSpace);
	auto iMesh = scene->mMeshes[0];

	for (int idx = 0; idx < iMesh->mNumVertices; ++idx)
	{
		Vertex vertex;

		vertex.position.x = iMesh->mVertices[idx].x;
		vertex.position.y = iMesh->mVertices[idx].y;
		vertex.position.z = iMesh->mVertices[idx].z;

		vertex.normal.x = iMesh->mNormals[idx].x;
		vertex.normal.y = iMesh->mNormals[idx].y;
		vertex.normal.z = iMesh->mNormals[idx].z;

		mesh->addVertex(vertex);
	}

	for (int idx = 0; idx < iMesh->mNumFaces; ++idx)
	{
		mesh->createTriangles(iMesh->mFaces[idx].mIndices[0], iMesh->mFaces[idx].mIndices[1], iMesh->mFaces[idx].mIndices[2]);
	}

	return mesh;
}