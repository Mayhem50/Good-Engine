#pragma once

namespace Good
{
	template <typename T>
	class Singleton
	{
	public:
		static T& getInstance()
		{
			if(_instance == NULL)
			{
				_instance = new T;
			}

			return *_instance;
		}

		static T* getInstancePtr()
		{
			if(_instance == NULL)
			{
				_instance = new T;
			}

			return _instance;
		}

	protected:
		Singleton(){}
		Singleton(const Singleton&){}
		Singleton& operator=(const Singleton&){return *this;}

		static T* _instance;
	};

	template <typename T>
	T* Singleton<T>::_instance = nullptr;
}