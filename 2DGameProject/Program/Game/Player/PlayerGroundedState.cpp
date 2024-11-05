#include "PlayerGroundedState.h"

#include "PlayerIdleState.h"
#include "PlayerWalkState.h"

namespace Downwell
{
	PlayerGroundedState::PlayerGroundedState(Player* context, State<Player>* parent)
		: State<Player>(context, parent)
	{
		AddChildState<PlayerIdleState>();
		AddChildState<PlayerWalkState>();

		// ‘Ò‹@ó‘Ô‘JˆÚğŒ
		AddChildTransition<PlayerIdleState, PlayerWalkState>(PLAYER_WALK);

		// •àsó‘Ô‘JˆÚğŒ
		AddChildTransition<PlayerWalkState, PlayerIdleState>(PLAYER_IDLE);

		RegisterStartState<PlayerIdleState>();
	}

	void PlayerGroundedState::OnEnter()
	{
		_gun = GetContext().GetComponent<Gun>();
		_gun->Reload();
	}

	void PlayerGroundedState::OnUpdate()
	{
		auto& context = GetContext();

		bool isOnGround = context.GetBoxCollider().IsOnGround();
		bool isTriggerJumpButtom = GamePad::Trigger(Xinput::A);
		bool canStep = context.IsStep();
		if (isOnGround == false || isTriggerJumpButtom || canStep == true)
		{
			SendTrigger(PLAYER_FLOATING);
			return;
		}
	}

	void PlayerGroundedState::OnExit()
	{


	}
}
