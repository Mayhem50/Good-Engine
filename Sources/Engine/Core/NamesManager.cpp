#include "NamesManager.h"

#include "GoodObject.h"

#include <random>
#include <algorithm>

using namespace Good;

std::string NamesManager::nameGenerator(GoodObject* object)
{
	std::random_device generator;
	std::uniform_int_distribution<int> sizeRand(10, 20);

	int nameLenght = sizeRand(generator);
	char* name = new char[nameLenght];

	memset(name, 0, nameLenght);

	for (int idx = 0; idx < nameLenght; ++idx)
	{
		std::uniform_int_distribution<int> asciiPart(1, 3);

		int part = asciiPart(generator);
		int begin = 0;
		int end = 0;

		switch (part)
		{
		default:
		case 1:
			begin = 48;
			end = 57;
			break;
		case 2:
			begin = 65;
			end = 90;
			break;
		case 3:
			begin = 97;
			end = 122;
			break;
		}

		std::uniform_int_distribution<int> letterChoose(begin, end);
		name[idx] = letterChoose(generator);
	}

	name[nameLenght] = '\0';

	return std::string(typeid(*object).name()) + "_" + std::string(name);
}

bool NamesManager::nameExist(const std::string& name) const
{
	return _namesList.find(name) != _namesList.end();
}

unsigned int NamesManager::namesContainCount(const std::string& str) const
{
	unsigned int count = 0;
	for ( auto name : _namesList)
	{
		if (name.find(str) != std::string::npos)
			++count;
	}

	return count;
}

bool NamesManager::addName(std::string& name)
{
	unsigned int count = namesContainCount(name);
	if (count != 0)
		name += std::to_string(count);

	auto ret = _namesList.insert(name);

	return ret.second;
}

bool NamesManager::removeName(const std::string& name)
{
	return _namesList.erase(name);
}