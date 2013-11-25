#pragma once
#include <string>

#include "../Core/GoodFoundationLib.h"

namespace Good
{
	class ILogger
	{
	public:
		virtual ~ILogger(void){}
		virtual bool write(const ::std::string str) const = 0;
	};
}

