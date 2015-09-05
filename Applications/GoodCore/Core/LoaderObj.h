#pragma once

#include "ILoader.h"

namespace Good
{
	namespace GeometryLoader
	{
		GOOD_DLL MeshPtr load(const char* file);
	}
}