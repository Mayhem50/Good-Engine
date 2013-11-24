#pragma once
#include "ilogger.h"
class LogFile :
	public ILogger
{
public:
	LogFile(const std::string file);
	~LogFile(void);
	virtual bool Log(const std::string log) const;

private:
};

