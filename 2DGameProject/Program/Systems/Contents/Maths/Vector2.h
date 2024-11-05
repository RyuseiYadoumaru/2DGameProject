#pragma once
#include <DirectXMath.h>

namespace myMath
{
	class Vector2 : public DirectX::XMFLOAT2
	{
	public:
		static const Vector2 Up;
		static const Vector2 Down;
		static const Vector2 Right;
		static const Vector2 Left;
		static const Vector2 Zero;
		static const Vector2 One;

	public:
		static Vector2 Normalize(const Vector2& inVec2);
		static Vector2 Inverse(const Vector2& inVec2);

	public:
		void Set(float _x, float _y) noexcept { x = _x; y = _y; }
		void Set(const DirectX::XMVECTOR& inXMVector) noexcept { DirectX::XMStoreFloat2(this, inXMVector); }
		DirectX::XMVECTOR GetXMVector() noexcept { return DirectX::XMVectorSet(x, y, 0.0f, 0.0f); }

	public:
		Vector2() : DirectX::XMFLOAT2(0.0f, 0.0f) {}
		Vector2(float _x, float _y) : DirectX::XMFLOAT2(_x, _y) {}

		Vector2& operator=(const Vector2& vec2) noexcept { x = vec2.x; y = vec2.y; return *this; }
		Vector2& operator=(const DirectX::XMFLOAT2& vec2) noexcept { x = vec2.x; y = vec2.y; return *this; }
		Vector2 operator+(const Vector2& vec2) const noexcept { return Vector2(x + vec2.x, y + vec2.y); }
		Vector2& operator+=(const Vector2& vec2)  noexcept { x += vec2.x; y += vec2.y; return *this; }
		Vector2 operator-(const Vector2& vec2) const noexcept { return Vector2(x - vec2.x, y - vec2.y); }
		Vector2& operator-=(const Vector2& vec2) noexcept { x -= vec2.x; y -= vec2.y; return *this; }
		Vector2 operator*(const Vector2& vec2) const noexcept { return Vector2(x * vec2.x, y * vec2.y); }
		Vector2& operator*=(const Vector2& vec2) noexcept { x *= vec2.x; y *= vec2.y; return *this; }
		Vector2 operator/(const Vector2& vec2) const noexcept { return Vector2(x / vec2.x, y / vec2.y); }
		Vector2& operator/=(const Vector2& vec2) noexcept { x /= vec2.x; y /= vec2.y; return *this; }
		bool operator!=(const Vector2& vec2)const noexcept { return (this->x != vec2.x && this->y != vec2.y); }
		bool operator==(const Vector2& vec2)const noexcept { return (this->x == vec2.x && this->y == vec2.y); }
	};
}