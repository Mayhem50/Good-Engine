#pragma once

#include "../Core/Singleton.h"
#include "LogFile.h"
#include "LogConsole.h"

namespace Good
{
	class LogManager : public Singleton<LogManager>
	{
	public:
		ILogger* LoggerToFile(const char* fileName = "./log.txt")
		{
			return new LogFile(fileName);
		}

		ILogger* LoggerToConsole()
		{
			return new LogConsole();
		}
	};
}

