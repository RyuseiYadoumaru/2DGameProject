#include "FloatingEnemyDiscoveryState.h"

namespace Downwell
{
	FloatingEnemyDiscoveryState::FloatingEnemyDiscoveryState(FloatingEnemy* context, State<FloatingEnemy>* parent)
		:State<FloatingEnemy>(context, parent)
	{

	}

	void FloatingEnemyDiscoveryState::OnEnter()
	{
		auto player = GameObject::Find("Player");
		if (player != nullptr)
		{
			_targetTrans = &player->GetTrans();
		}
	}

	void FloatingEnemyDiscoveryState::OnUpdate()
	{
		bool isAppearCamera = Camera::CheckAppearCamera(GetContext().GetTrans());
		if (isAppearCamera == false)
		{
			SendTrigger(FLOATINGENEMY_PATROL);
			return;
		}

		auto enemy = GetContext();
		if (_targetTrans != nullptr)
		{
			// ターゲットが定まっていたらその方向に向かう
			Vector2 moveVec = _targetTrans->position - enemy.GetTrans().position;
			moveVec = Vector2::Normalize(moveVec);

			Vector2 force;
			force.x = moveVec.x * enemy.GetMoveSpeed();
			force.y = moveVec.y * enemy.GetMoveSpeed();
			enemy.GetTrans().moveForce = force;
		}
	}

	void FloatingEnemyDiscoveryState::OnExit()
	{
		_targetTrans = nullptr;
		GetContext().GetTrans().moveForce.Set(0.0f, 0.0f);
	}
}