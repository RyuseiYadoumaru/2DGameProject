#include "CrawlEnemyMovementState.h"
#include "EnemyManager.h"

namespace Downwell
{
	CrawlEnemyMovementState::CrawlEnemyMovementState(CrawlEnemy* context, State<CrawlEnemy>* parent)
		:State<CrawlEnemy>(context, parent)
	{
	}


	void CrawlEnemyMovementState::OnEnter()
	{
	}

	void CrawlEnemyMovementState::OnUpdate()
	{
		auto& enemy = GetContext();
		// カメラの範囲外にいったらアイドルに戻す
		bool isAppearCamera = Camera::CheckAppearCamera(enemy.GetTrans(), 0.0f, 100.0f);
		if (isAppearCamera == false)
		{
			SendTrigger(CRAWL_IDLE);
			return;
		}

		Vector2 moveForce = Vector2::Zero;
		if (enemy.GetIsFall() == true)
		{
			_fallFrameCounter++;
			if (_fallFrameCounter >= _fallMaxSpeedFrame) _fallFrameCounter = _fallMaxSpeedFrame;
			moveForce.y = enemy.GetFallMaxSpeed() * Easing::SineOut(static_cast<float>(_fallFrameCounter),
																	static_cast<float>(_fallMaxSpeedFrame),
																	0.0f, 1.0f);
		}
		else
		{
			moveForce.x = enemy.GetMoveVector().x * enemy.GetMoveSpeed();
			moveForce.y = enemy.GetMoveVector().y * enemy.GetMoveSpeed();
			_fallFrameCounter = 0;
		}

		enemy.GetTrans().moveForce = moveForce;
	}

	void CrawlEnemyMovementState::OnExit()
	{
		if (GetContext().GetIsFall() == true)
		{
			// 落下のままカメラ外に出たら死亡にする
			EnemyManager::Remove(&GetContext());
		}
	}
}