#pragma once

#include "ILoader.h"

namespace Good
{
	class LoaderObj : public ILoader
	{
	public:
		virtual ModelPtr load(const char* file);
	};
}