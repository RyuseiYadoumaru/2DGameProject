#pragma once
#include "FloatingEnemy.h"

namespace Downwell
{
	class FloatingEnemyIdleSate : public State<FloatingEnemy>
	{
	public:
		FloatingEnemyIdleSate(FloatingEnemy* context, State<FloatingEnemy>* parent);



		// State ����Čp������܂���
		virtual void OnEnter() override;

		virtual void OnUpdate() override;

		virtual void OnExit() override;

	};
}