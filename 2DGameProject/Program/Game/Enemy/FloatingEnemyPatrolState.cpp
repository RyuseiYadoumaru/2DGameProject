#include "FloatingEnemyPatrolState.h"

#include "FloatingEnemyIdleState.h"
#include "FloatingEnemyMovementState.h"

namespace Downwell
{
	FloatingEnemyPatrolState::FloatingEnemyPatrolState(FloatingEnemy* context, State<FloatingEnemy>* parent)
		:State<FloatingEnemy>(context, parent)
	{
		AddChildState<FloatingEnemyIdleSate>();
		AddChildState<FloatingEnemyMovementState>();

		// �ړ��J�ڐ�
		AddChildTransition<FloatingEnemyMovementState, FloatingEnemyIdleSate>(FLOATING_PATROL_IDLE);
		
		// �ҋ@�J�ڐ�
		AddChildTransition<FloatingEnemyIdleSate, FloatingEnemyMovementState>(FLOATING_PATROL_MOVEMENT);

		RegisterStartState<FloatingEnemyIdleSate>();
	}

	void FloatingEnemyPatrolState::OnEnter()
	{

	}

	void FloatingEnemyPatrolState::OnUpdate()
	{
		bool isAppearCamera = Camera::CheckAppearCamera(GetContext().GetTrans());
		if (isAppearCamera == true)
		{
			SendTrigger(FLOATINGENEMY_DISCOVERY);
		}
	}

	void FloatingEnemyPatrolState::OnExit()
	{
	}
}