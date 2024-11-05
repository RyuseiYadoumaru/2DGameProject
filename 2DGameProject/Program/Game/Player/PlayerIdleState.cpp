#include "PlayerIdleState.h"

#include "../Include/SystemInclude.h"

namespace Downwell
{
	PlayerIdleState::PlayerIdleState(Player* context, State<Player>* parent)
		: State<Player>(context, parent)
	{
	}

	void PlayerIdleState::OnEnter()
	{
		GetContext().SetColor(30.0f, 30.0f, 205.0f);

	}

	void PlayerIdleState::OnUpdate()
	{
		auto& context = GetContext();
		context.GetTrans().moveForce.Set(0.0f, 0.0f);

		if (GamePad::LStick().x != 0.0f)
		{
			// ï‡çsèÛë‘Ç…ëJà⁄
			SendTrigger(PLAYER_WALK);
			return;
		}

	}

	void PlayerIdleState::OnExit()
	{
	}
}