#include "PlayerWalkState.h"

#include "../Include/SystemInclude.h"

namespace Downwell
{
	PlayerWalkState::PlayerWalkState(Player* context, State<Player>* parent)
		: State<Player>(context, parent)
	{
	}

	void PlayerWalkState::OnEnter()
	{
		_frame = 0;
		GetContext().SetColor(0.0f, 0.0f, 255.0f);
	}

	void PlayerWalkState::OnUpdate()
	{
		auto& context = GetContext();
		float stick = GamePad::LStick().x;
		if (stick == 0.0f)
		{
			// ë“ã@èÛë‘Ç…ëJà⁄
			SendTrigger((int)PLAYER_IDLE);
			return;
		}

		Transform& trans = context.GetTrans();
		context.GetActionEvent().Movement(&trans, context.GetWalkMaxSpeed(), stick, _frame);
		//context.GetActionEvent().Fall(&trans, context.GetFallMaxSpeed(), context.GetFallMaxSpeedFrame(), 15);

		_frame++;

	}

	void PlayerWalkState::OnExit()
	{
	}
}