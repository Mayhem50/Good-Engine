#pragma once

#include "../Math/Vectors.h"

namespace Good
{
	struct Color
	{
		Color():red(1), green(1), blue(1), alpha(1){}

		Color(const Vector4& color)
		{
			red = color.x; green = color.y;
			blue = color.z; alpha = color.w;
		}

		Color(Real red_,Real green_, Real blue_, Real alpha_)
		{
			red = red_; green = green_;
			blue = blue_; alpha = alpha_;
		}

		Color(Real val)
		{
			red = val; green = val;
			blue = val; alpha = 1.0;
		}

		Color operator+(const Color& rColor) const
		{
			return Color(
				red + rColor.red,
				green + rColor.green,
				blue + rColor.blue,
				alpha + rColor.alpha);
		}

		Color operator*(const Color& rColor) const
		{
			return Color(
				red * rColor.red,
				green * rColor.green,
				blue * rColor.blue,
				alpha * rColor.alpha);
		}

		Color operator-(const Color& rColor) const
		{
			return Color(
				red - rColor.red,
				green - rColor.green,
				blue - rColor.blue,
				alpha - rColor.alpha);
		}

		Color operator/(const Color& rColor) const
		{
			return Color(
				red / rColor.red,
				green / rColor.green,
				blue / rColor.blue,
				alpha / rColor.alpha);
		}

		Color operator+(Real scalar) const
		{
			return Color(
				red + scalar,
				green + scalar,
				blue + scalar,
				alpha);
		}

		Color operator*(Real scalar) const
		{
			return Color(
				red * scalar,
				green * scalar,
				blue * scalar,
				alpha);
		}

		Color operator-(Real scalar) const
		{
			return Color(
				red - scalar,
				green - scalar,
				blue - scalar,
				alpha);
		}

		Color operator/(Real scalar) const
		{
			return Color(
				red / scalar,
				green / scalar,
				blue / scalar,
				alpha);
		}

		Color& operator+=(const Color& rColor)
		{
			red += rColor.red;
			green += rColor.green;
			blue += rColor.blue;
			alpha += rColor.alpha;

			return *this;
		}

		Color& operator*=(const Color& rColor)
		{
			red *= rColor.red;
			green *= rColor.green;
			blue *= rColor.blue;
			alpha *= rColor.alpha;

			return *this;
		}

		Color& operator-=(const Color& rColor)
		{
			red -= rColor.red;
			green -= rColor.green;
			blue -= rColor.blue;
			alpha -= rColor.alpha;

			return *this;
		}

		Color& operator/=(const Color& rColor)
		{
			red /= rColor.red;
			green /= rColor.green;
			blue /= rColor.blue;
			alpha /= rColor.alpha;

			return *this;
		}

		Color& operator+=(Real scalar)
		{
			red += scalar;
			green += scalar;
			blue += scalar;

			return *this;
		}

		Color& operator*=(Real scalar)
		{
			red *= scalar;
			green *= scalar;
			blue *= scalar;

			return *this;
		}

		Color& operator-=(Real scalar)
		{
			red -= scalar;
			green -= scalar;
			blue -= scalar;

			return *this;
		}

		Color& operator/=(Real scalar)
		{
			red /= scalar;
			green /= scalar;
			blue /= scalar;

			return *this;
		}

		friend Color operator+(Real scalar, const Color& rColor)
		{
			return (rColor + scalar);
		}

		friend Color operator-(Real scalar, const Color& rColor)
		{
			return rColor.operator-(scalar);
		}

		friend Color operator*(Real scalar, const Color& rColor)
		{
			return rColor.operator*(scalar);
		}

		friend Color operator/(Real scalar, const Color& rColor)
		{
			return rColor.operator/(scalar);
		}

		Real red, green, blue, alpha;
	};
}