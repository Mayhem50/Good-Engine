#include "LogFile.h"

#include "../../Engine/Core/GoodObject.h"

#include <fstream>
#include <time.h>

using namespace Good;

LogFile::LogFile(const char* fileName)
{	
	_fileName = const_cast<char*>(fileName);
	std::ofstream file;
	file.open(_fileName, std::ios::out | std::ios::trunc);
	file.close();
}

LogFile::~LogFile(void)
{
	delete[] _fileName;
}

bool LogFile::write(const std::string& str, const GoodObject* object) const
{
	std::ofstream file;
	file.open(_fileName, std::ios::out | std::ios::app);

	if(file.is_open())
	{
		time_t timer;
		struct tm *timeInfo = new struct tm;
		char buffer[1024];

		time(&timer);
		localtime_s(timeInfo, &timer);
		asctime_s(buffer, timeInfo);
		std::string newStr(buffer);
		newStr.replace(newStr.find_first_of("\n") , 1, "\0");

		if (object)
			file << typeid(*object).name() << " send ";

		file << newStr << ": " << str << std::endl;

		file.close();
		return true;
	}

	else
		return false;
}
