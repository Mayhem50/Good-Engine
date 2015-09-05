#pragma once

#include "../Core/Singleton.h"
#include "LogFile.h"
#include "LogConsole.h"

namespace Good
{
	class LogManager : public Singleton<LogManager>
	{
	public:
		ILoggerPtr LoggerToFile(const char* fileName = "./log.txt")
		{
			return new LogFile(fileName);
		}

		ILoggerPtr LoggerToConsole()
		{
			return new LogConsole();
		}
	};
}

