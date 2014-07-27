#pragma once
#include "ILogger.h"

namespace Good
{
	class GOOD_DLL LogFile : public ILogger
	{
	public:
		LogFile(const char* fileName);
		virtual ~LogFile(void);
		virtual bool write(const std::string& str, const GoodObject* object = nullptr) const;

	private:
		char* _fileName;
	};
}

