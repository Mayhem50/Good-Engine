#include "LogConsole.h"
#include <iostream>
#include <typeinfo>

using namespace Good;

LogConsole::LogConsole()
{}

LogConsole::~LogConsole()
{}

bool LogConsole::write(const std::string& str, const GoodObject* object) const
{
	if (object)
		std::cout << typeid(*object).name() << " send\n\t";

	std::cout << str.c_str() << std::endl;
	return true;
}