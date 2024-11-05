#include "Vector2.h"
#include "../../Typedef/Typedef.h"

namespace myMath
{
	const Vector2 Vector2::Up		( 0.0f, -1.0f);
	const Vector2 Vector2::Down		( 0.0f,  1.0f);
	const Vector2 Vector2::Right	( 1.0f,  0.0f);
	const Vector2 Vector2::Left		(-1.0f,  0.0f);
	const Vector2 Vector2::Zero		( 0.0f,  0.0f);
	const Vector2 Vector2::One		( 1.0f,  1.0f);

	Vector2 Vector2::Normalize(const Vector2& inVec2)
	{
		ALIGN16 DirectX::XMVECTOR inVec;
		ALIGN16 DirectX::XMVECTOR outVec;

		inVec = DirectX::XMLoadFloat2(&inVec2);
		outVec = DirectX::XMVector2Normalize(inVec);

		Vector2 out;
		out.Set(outVec);
		return out;
	}

	Vector2 Vector2::Inverse(const Vector2& inVec2)
	{
		Vector2 outVec;
		outVec.x = inVec2.x * -1.0f;
		outVec.y = inVec2.y * -1.0f;

		outVec = Normalize(outVec);

		return outVec;
	}
}