#include "PlayerActionState.h"

#include "PlayerGroundedState.h"
#include "PlayerFloatingState.h"

#include "../Enemy/EnemyManager.h"

#include "../Include/SystemInclude.h"
#include "../Include/MathInclude.h"


namespace Downwell
{
	PlayerActionState::PlayerActionState(Player* context, State<Player>* parent)
		: State<Player>(context, parent)
	{
		AddChildState<PlayerGroundedState>();
		AddChildState<PlayerFloatingState>();

		// 地面状態遷移条件
		AddChildTransition<PlayerGroundedState, PlayerFloatingState>(PLAYER_FLOATING);

		// 浮遊状態遷移条件
		AddChildTransition<PlayerFloatingState, PlayerGroundedState>(PLAYER_GROUND);

		RegisterStartState<PlayerFloatingState>();
	}

	void PlayerActionState::OnEnter()
	{
		printf("アクション開始\n");

		_fallTimer = 0.0f;
	}

	void PlayerActionState::OnUpdate()
	{
		Player& player = GetContext();

		auto collider = player.GetBoxCollider();
		vector<HitEnemyInfo> hitEnemyList = EnemyManager::HitCheckEnemy(collider);
		for (auto& info : hitEnemyList)
		{
			auto hitEnemy = info.hitEnemy;

			bool isHitButtom = (player.GetTrans().position.y < hitEnemy->GetTrans().position.y);
			bool isHitTagFloatingEnemy = (hitEnemy->GetTag() == Tag::FloatingEnemy);
			bool canStep = (player.IsStep() == false);
			if ( isHitButtom == true &&
				 isHitTagFloatingEnemy == true &&
				 canStep == true)
			{
				// 下が当たって浮遊敵だったら踏みつける
				player.OnStartStep();
			}
			else
			{
				// それ以外のヒット判定ならダメージを受ける
				player.GetLife().OnDamage();
				int currentLifePoint = player.GetLife().GetLifePoint();
				if (currentLifePoint == 0)
				{
					// 死亡した
					player.OnDeath();
					SendTrigger(PLAYER_DEATH);
				}
				else
				{
					// 死亡していないときの処理
					player.OnDamage();
				}
			}

			EnemyManager::Remove(hitEnemy);
		}
	}

	void PlayerActionState::OnExit()
	{
		printf("アクション終了\n");
	}

}