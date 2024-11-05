#pragma once
#include "FloatingEnemy.h"

namespace Downwell
{
	class FloatingEnemyMovementState : public State<FloatingEnemy>
	{
	public:
		FloatingEnemyMovementState(FloatingEnemy* context, State<FloatingEnemy>* parent);

	public:
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;
	};
}