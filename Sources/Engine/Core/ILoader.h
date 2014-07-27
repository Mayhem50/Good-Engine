#pragma once

#include "GoodFoundation.h"
#include "../Mesh/Mesh.h"

namespace Good
{
	class GOOD_DLL ILoader
	{
	public:
		virtual MeshPtr load(const char* file) = 0;
	};
}