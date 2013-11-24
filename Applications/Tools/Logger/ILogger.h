#pragma once
#include <string>

#include "Export.h"

class EXPORT_DLL ILogger
{
public:
	virtual ~ILogger(void) = 0;
	virtual bool Log(const std::string log) const = 0;
};

