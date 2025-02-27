#include "PlayerFireState.h"

#include "../Include/SystemInclude.h"

namespace Downwell
{
	PlayerFireState::PlayerFireState(Player* context, State<Player>* parent)
		: State<Player>(context, parent)
	{

	}

	void PlayerFireState::OnEnter()
	{
		_gun = GetContext().GetComponent<Gun>();
		if (_gun == nullptr)
		{
			printf("Not Gun Component!!!!!!!\n");
		}
		_frame = 0;
		_fireFrame = GetContext().GetFireIntervalFrame();;
		GetContext().SetColor(200.0f, 0.0f, 20.0f);

		GetContext().GetTrans().moveForce.Set(0.0f, 0.0f);
	}

	void PlayerFireState::OnUpdate()
	{
		auto& context = GetContext();

		// 着地判定
		bool isOnGround = context.GetBoxCollider().IsOnGround();
		if (isOnGround == true)
		{
			SendTrigger(PLAYER_GROUND);
			return;
		}

		// 弾発射終了
		if (GamePad::Press(Xinput::A) == false ||
			_gun->GetRemainingBulletsNum() == 0)
		{
			SendTrigger(PLAYER_FALL);
			return;
		}

		// 落下
		// 弾発射中はゆっくりになる
		Transform& trans = context.GetTrans();
		context.GetActionEvent().Fall(&trans, 0.3f, context.GetFallMaxSpeedFrame(), _frame);
		
		// 移動
		float stick = GamePad::LStick().x;
		context.GetActionEvent().Movement(&trans, context.GetWalkMaxSpeed(), stick, _frame);
		
		// 弾発射
		const int fireInterval = context.GetFireIntervalFrame();
		if (_fireFrame >= fireInterval)
		{
			_fireFrame = 0;
			_gun->Fire();
		}

		_frame++;
		_fireFrame++;
	}

	void PlayerFireState::OnExit()
	{


	}
}
