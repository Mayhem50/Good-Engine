#pragma once

#include "Singleton.h"

#include <string>
#include <set>

namespace Good
{
	class GoodObject;

	class GOOD_DLL NamesManager : public Singleton<NamesManager>
	{
	public:
		std::string nameGenerator(GoodObject* object);

		bool addName(std::string& name);
		bool removeName(const std::string& name);

	private:
		bool nameExist(const std::string& name) const;
		unsigned int namesContainCount(const std::string& str) const;

		std::set<std::string> _namesList;
	};
}