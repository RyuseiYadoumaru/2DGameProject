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
		printf("�����J�n\n");
	}

	void PlayerFallState::OnUpdate()
	{
		auto& context = GetContext();
		Transform& trans = context.GetTrans();

		// ���n����
		bool isOnGround = context.GetBoxCollider().IsOnGround();
		if (isOnGround == true)
		{
			SendTrigger(PLAYER_GROUND);
			return;
		}

		// �e����
		if (GamePad::Trigger(Xinput::A))
		{
			SendTrigger(PLAYER_FIRE);
			return;
		}

		// �G���݂�
		if (context.IsStep() == true)
		{
			SendTrigger(PLAYER_STEP);
			return;
		}

		// �t���[���X�V�㋓�����s��
		_frame++;

		// �ړ�����
		float stick = GamePad::LStick().x;
		context.GetActionEvent().Movement(&trans, context.GetWalkMaxSpeed(), stick, _frame);

		// ��������
		context.GetActionEvent().Fall(&trans, context.GetFallMaxSpeed(), context.GetFallMaxSpeedFrame(), _frame);		
	}

	void PlayerFallState::OnExit()
	{
		GetContext().GetTrans().moveForce.Set(0.0f, 0.0f);
	}
}
