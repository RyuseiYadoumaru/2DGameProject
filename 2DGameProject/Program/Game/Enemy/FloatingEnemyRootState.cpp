#include "FloatingEnemyRootState.h"

#include "FloatingEnemyPatrolState.h"
#include "FloatingEnemyDiscoveryState.h"

namespace Downwell
{
	FloatingEnemyRootState::FloatingEnemyRootState(FloatingEnemy* context, State<FloatingEnemy>* parent)
		:State<FloatingEnemy>(context, parent)
	{
		AddChildState<FloatingEnemyPatrolState>();
		AddChildState<FloatingEnemyDiscoveryState>();
		
		// ����J�ڐ�
		AddChildTransition<FloatingEnemyPatrolState, FloatingEnemyDiscoveryState>(FLOATINGENEMY_DISCOVERY);
		
		// �����J�ڐ�
		AddChildTransition<FloatingEnemyDiscoveryState, FloatingEnemyPatrolState>(FLOATINGENEMY_PATROL);

		RegisterStartState<FloatingEnemyPatrolState>();
	}

	void FloatingEnemyRootState::OnEnter()
	{
	}

	void FloatingEnemyRootState::OnUpdate()
	{
	}

	void FloatingEnemyRootState::OnExit()
	{
	}
}