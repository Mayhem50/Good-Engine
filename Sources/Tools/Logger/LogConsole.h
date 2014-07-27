#pragma once
#include "Ilogger.h"

namespace Good
{
	class GOOD_DLL LogConsole : public ILogger
	{
	public:
		LogConsole();
		virtual ~LogConsole(void);
		virtual bool write(const std::string& str, const GoodObject* object = nullptr) const;
	};
}

