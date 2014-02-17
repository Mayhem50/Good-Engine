#pragma once

namespace Good
{
	template <typename T>
	class GOOD_DLL Singleton
	{
	public:
		static T* getInstancePtr()
		{
			if(_instance == nullptr)
				_instance = new T;

			return _instance;
		}
		
		template <typename _A1>
		static T* getInstancePtr(_A1 a1)
		{
			if (_instance == nullptr)
				_instance = new T(a1);

			return _instance;
		}

		template <typename _A1, typename _A2>
		static T* getInstancePtr(_A1 a1, _A2 a2)
		{
			if (_instance == nullptr)
				_instance = new T(a1, a2);

			return _instance;
		}

		template <typename _A1, typename _A2, typename _A3>
		static T* getInstancePtr(_A1 a1, _A2 a2, _A3 a3)
		{
			if (_instance == nullptr)
				_instance = new T(a1, a2, a3);

			return _instance;
		}

		template <typename _A1, typename _A2, typename _A3, typename _A4>
		static T* getInstancePtr(_A1 a1, _A2 a2, _A3 a3, _A4 a4)
		{
			if (_instance == nullptr)
				_instance = new T(a1, a2, a3, a4);

			return _instance;
		}

		template <typename _A1, typename _A2, typename _A3, typename _A4, typename _A5>
		static T* getInstancePtr(_A1 a1, _A2 a2, _A3 a3, _A4 a4, _A5 a5)
		{
			if (_instance == nullptr)
				_instance = new T(a1, a2, a3, a4, a5);

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