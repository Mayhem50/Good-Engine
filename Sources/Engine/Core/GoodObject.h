#pragma once

#include "NamesManager.h"

#include <string>
#include <rpc.h>

#ifdef _DEBUG
#pragma comment(lib, "Logger")
#include "../../Tools/Logger/ILogger.h"
#include "../../Tools/Logger/LogConsole.h"
#endif

namespace Good
{
	typedef GUID Uuid;

	class GoodObject
	{
	public:
		GoodObject(const std::string& name):
			_name(name)
		{
			_initalize();
		}

		GoodObject(const char*  name = nullptr):
			_name(name)
		{
			_initalize();
		}

		virtual ~GoodObject() 
		{
			NamesManager::getInstancePtr()->removeName(_name);
		}

		const std::string& name() const
		{
			return _name;
		}

		std::string& name() 
		{
			return _name;
		}

		const Uuid& uuid() const
		{
			return _uuid;
		}

		Uuid& uuid() 
		{
			return _uuid;		// Regarder dans le boucain pour le const_cast
		}

	protected:
		std::string _name;
		Uuid _uuid;

#ifdef _DEBUG
		ILoggerPtr _logger;
#endif

	private:
		void _initalize()
		{
			if (_name.empty())
				_name = NamesManager::getInstancePtr()->nameGenerator(this);

			NamesManager::getInstancePtr()->addName(_name);

#ifdef _DEBUG
			_logger = ILoggerPtr(new LogConsole());
#endif
		}
	};
}