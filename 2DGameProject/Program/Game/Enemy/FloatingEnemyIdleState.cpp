#include "FloatingEnemyIdleState.h"

namespace Downwell
{
	FloatingEnemyIdleSate::FloatingEnemyIdleSate(FloatingEnemy* context, State<FloatingEnemy>* parent)
		:State<FloatingEnemy>(context, parent)
	{
	}

	void FloatingEnemyIdleSate::OnEnter()
	{
	}

	void FloatingEnemyIdleSate::OnUpdate()
	{
		FloatingEnemy& enemy = GetContext();
		enemy.GetTrans().moveForce.Set(0.0f, 0.0f);
	
	}

	void FloatingEnemyIdleSate::OnExit()
	{
	}
}