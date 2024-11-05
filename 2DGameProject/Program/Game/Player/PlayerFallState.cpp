#include "PlayerFallState.h"
#include "../Gun/Gun.h"

#include "../Include/SystemInclude.h"

namespace Downwell
{
	PlayerFallState::PlayerFallState(Player* context, State<Player>* parent)
		: State<Player>(context, parent)
	{

	}

	void PlayerFallState::OnEnter()
	{
		auto gun = GetContext().GetComponent<Gun>();
		_frame = (gun->GetRemainingBulletsNum() == 0) ? 3 : 0;
		GetContext().SetColor(0.0f, 150.0f, 20.0f);
		auto& trans = GetContext().GetTrans();
		trans.moveForce.Set(0.0f, 0.0f);
		printf("落下開始\n");
	}

	void PlayerFallState::OnUpdate()
	{
		auto& context = GetContext();
		Transform& trans = context.GetTrans();

		// 着地判定
		bool isOnGround = context.GetBoxCollider().IsOnGround();
		if (isOnGround == true)
		{
			SendTrigger(PLAYER_GROUND);
			return;
		}

		// 弾発射
		if (GamePad::Trigger(Xinput::A))
		{
			SendTrigger(PLAYER_FIRE);
			return;
		}

		// 敵踏みつけ
		if (context.IsStep() == true)
		{
			SendTrigger(PLAYER_STEP);
			return;
		}

		// フレーム更新後挙動を行う
		_frame++;

		// 移動処理
		float stick = GamePad::LStick().x;
		context.GetActionEvent().Movement(&trans, context.GetWalkMaxSpeed(), stick, _frame);

		// 落下処理
		context.GetActionEvent().Fall(&trans, context.GetFallMaxSpeed(), context.GetFallMaxSpeedFrame(), _frame);		
	}

	void PlayerFallState::OnExit()
	{
		GetContext().GetTrans().moveForce.Set(0.0f, 0.0f);
	}
}
