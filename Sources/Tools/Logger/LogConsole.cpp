#include "LogConsole.h"

#include "../../Engine/Core/GoodObject.h"

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
		std::cout << object->name() << "(" << typeid(*object).name() << ") send:\t";

	std::cout << str.c_str() << std::endl;
	return true;
}