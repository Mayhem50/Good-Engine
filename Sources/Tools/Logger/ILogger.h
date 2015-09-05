#pragma once

#include "../../Engine/Core/GoodFoundation.h"

#include <string>
#include <memory>

namespace Good
{
	class GoodObject;

	class GOOD_DLL ILogger
	{
	public:
		virtual ~ILogger(void){}
		virtual bool write(const ::std::string& str, const GoodObject* object = nullptr) const = 0;
	};

	typedef std::shared_ptr<ILogger> ILoggerPtr;
}

