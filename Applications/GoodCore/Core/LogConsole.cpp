#include "LogConsole.h"
#include <iostream>

using namespace Good;

bool LogConsole::write(const std::string str) const 
{
	std::cout << str << std::endl;
	return true;
}

LogConsole::~LogConsole()
{

}
