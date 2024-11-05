#include "Transform.h"

namespace myGame::Object
{

#pragma region System Callback Function

	void Transform::Initialize()
	{
		SetOrder(10);

		moveForce.Set(0.0f, 0.0f);
	}

	void Transform::Finalize()
	{
	}

	void Transform::Start()
	{
	}

	void Transform::Update()
	{
	}

	void Transform::SecondUpdate()
	{
		_moveVector = myMath::Vector2::Normalize(moveForce);
		position.x += moveForce.x;
		position.y += moveForce.y;
	}

	void Transform::LateUpdate()
	{
	}

	void Transform::End()
	{
	}
#pragma endregion
}