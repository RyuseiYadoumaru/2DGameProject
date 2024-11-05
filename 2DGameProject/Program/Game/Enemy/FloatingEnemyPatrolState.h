#pragma  once
#include "FloatingEnemy.h"

namespace Downwell
{
	class FloatingEnemyPatrolState : public State<FloatingEnemy>
	{
	public:
		FloatingEnemyPatrolState(FloatingEnemy* context, State<FloatingEnemy>* parent);

	public:
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;
	};
}