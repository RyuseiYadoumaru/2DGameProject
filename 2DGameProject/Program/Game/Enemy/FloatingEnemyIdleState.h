#pragma once
#include "FloatingEnemy.h"

namespace Downwell
{
	class FloatingEnemyIdleSate : public State<FloatingEnemy>
	{
	public:
		FloatingEnemyIdleSate(FloatingEnemy* context, State<FloatingEnemy>* parent);



		// State を介して継承されました
		virtual void OnEnter() override;

		virtual void OnUpdate() override;

		virtual void OnExit() override;

	};
}