#pragma once

#include <memory>

namespace Good
{
	class Viewport
	{
	public:
		Viewport();
		Viewport(int x, int y, int width, int height);
		~Viewport();

		void set(int x, int y, int width, int height);

		float aspect() const;
		int X() const;
		int Y() const;
		int width() const;
		int height() const;

	private:
		void _updateViewport();

		int _x;
		int _y;
		int _width;
		int _height;
	};

	typedef std::shared_ptr<Viewport> ViewportPtr;
}