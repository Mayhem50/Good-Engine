#pragma once

#include "../Core/Singleton.h"

namespace Good
{
	class GOOD_DLL Engine : public Singleton<Engine>
	{
	public:
		bool initailize();
		void predraw();
		void draw();
		void postdraw();

	private:

	};
}
