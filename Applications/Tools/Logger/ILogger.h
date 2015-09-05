#pragma once
#include <string>

#include "../../GoodCore/Core/GoodFoundation.h"

class GOOD_DLL ILogger
{
public:
	virtual ~ILogger(void) = 0;
	virtual bool Log(const std::string log) const = 0;
};

