#pragma  once
#include "FloatingEnemy.h"

namespace Downwell
{
	class FloatingEnemyRootState : public State<FloatingEnemy>
	{
	public:
		FloatingEnemyRootState(FloatingEnemy* context, State<FloatingEnemy>* parent);

	public:
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;
	};
}