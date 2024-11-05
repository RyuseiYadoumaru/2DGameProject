#pragma once

#include <DirectXMath.h>


namespace myMath
{
	class Color
	{
	public:
		void Set(float _r, float _g, float _b, float _a) noexcept { r = _r; g = _g; b = _b; a = _a; }

	public:
		float r;
		float g;
		float b;
		float a;

	public:
		float* GetFloat() noexcept
		{
			_colorFloat[0] = r;
			_colorFloat[1] = g;
			_colorFloat[2] = b;
			_colorFloat[3] = a;
			return _colorFloat;
		}

		DirectX::XMFLOAT4 GetXMFLOAT() noexcept
		{
			DirectX::XMFLOAT4 color;
			color.x = r;
			color.y = g;
			color.z = b;
			color.w = a;
			return color;
		}



	public:
		static const Color Black;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Magenta;
		static const Color Yellow;
		static const Color Cyan;
		static const Color Gray;
		static const Color White;
		static const Color Clear;

	public:

		Color() : r(255.0f), g(255.0f), b(255.0f), a(255.0f) {}
		Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}
		Color(Color& color) : r(color.r), g(color.g), b(color.b), a(color.a) {}
		Color(const Color&) = default;

		Color& operator=(const Color& color) noexcept { r = color.r; g = color.g; b = color.b; a = color.a; return *this; }
		Color operator+(const Color& color) const noexcept { return Color(r + color.r, g + color.g, b + color.b, a + color.a); }
		Color operator-(const Color& color) const noexcept { return Color(r - color.r, g - color.g, b - color.b, a - color.a); }
		Color operator*(const Color& color) const noexcept { return Color(r * color.r, g * color.g, b * color.b, a * color.a); }
		Color operator/(const Color& color) const noexcept { return Color(r / color.r, g / color.g, b / color.b, a / color.a); }
		bool operator!=(const Color& color) const noexcept { return (r != color.r && g != color.g && b != color.b && a != color.a); }
		bool operator==(const Color& color) const noexcept { return (r == color.r && g == color.g && b == color.b && a == color.a); }

	private:
		float _colorFloat[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	};

}