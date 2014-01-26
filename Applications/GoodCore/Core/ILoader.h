#pragma once

#include "GoodFoundation.h"
#include "Model.h"

namespace Good
{
	class GOOD_DLL ILoader
	{
	public:
		virtual ModelPtr load(const char* file) = 0;
	};
}