#pragma once

#include "../Core/ILoader.h"

namespace Good
{
	class GOOD_DLL LoaderObj : public ILoader
	{
	public:
		virtual MeshPtr load(const char* file);
	};
}