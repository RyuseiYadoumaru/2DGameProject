#include "PlayerJumpState.h"

#include "../Include/SystemInclude.h"

namespace Downwell
{
	PlayerJumpState::PlayerJumpState(Player* context, State<Player>* parent)
		: State<Player>(context, parent)
	{

	}

	void PlayerJumpState::OnEnter()
	{
		_jumpFrameCounter = 0;
		_currentRisePower = GetContext().GetJumpPower();

		_floatingFrameCounter = 0;
		isFloating = false;

		GetContext().SetColor(0.0f, 150.0f, 20.0f);
	}

	void PlayerJumpState::OnUpdate()
	{
		auto& context = GetContext();

		if (isFloating == true)
		{
			// �W�����v��A���t���[���̕��V���Ԃ�݂���
			if (_floatingFrameCounter >= context.GetJumpFloatingFrame())
			{
				SendTrigger(PLAYER_FALL);
				return;
			}
			_floatingFrameCounter++;
		}
		else
		{
			// �W�����v�I���̃t���O�Q
			bool isPressJumpButtom = GamePad::Press(Xinput::A);
			bool isHitTop = context.GetBoxCollider().IsHitTop();
			if (isPressJumpButtom == false ||
				_currentRisePower == 0.0f ||
				isHitTop == true)
			{
				isFloating = true;
			}

			// �W�����v�A�N�V����
			printf("�W�����v���I\n");
			context.GetActionEvent().Rise(&context.GetTrans(), &_currentRisePower, context.GetJumpPower(), context.GetRisingFrame(), _jumpFrameCounter);

		}

		// �ړ��A�N�V����
		float stick = GamePad::LStick().x;
		context.GetActionEvent().Movement(&context.GetTrans(), context.GetWalkMaxSpeed(), stick, _jumpFrameCounter);
		_jumpFrameCounter++;

	}

	void PlayerJumpState::OnExit()
	{


	}
}
