#include "PlayerFloatingState.h"

#include "PlayerFloatingEnterState.h"
#include "PlayerJumpState.h"
#include "PlayerFallState.h"
#include "PlayerFireState.h"
#include "PlayerStepState.h"

#include "../Include/SystemInclude.h"

namespace Downwell
{
	PlayerFloatingState::PlayerFloatingState(Player* context, State<Player>* parent)
		: State<Player>(context, parent)
	{
		AddChildState<PlayerFloatingEnterState>();
		AddChildState<PlayerJumpState>();
		AddChildState<PlayerFallState>();
		AddChildState<PlayerFireState>();
		AddChildState<PlayerStepState>();

		// ŠJn‘JˆÚæ
		AddChildTransition<PlayerFloatingEnterState, PlayerFallState>(PLAYER_FALL);
		AddChildTransition<PlayerFloatingEnterState, PlayerJumpState>(PLAYER_JUMP);
		AddChildTransition<PlayerFloatingEnterState, PlayerStepState>(PLAYER_STEP);

		// ƒWƒƒƒ“ƒv‘JˆÚæ
		AddChildTransition<PlayerJumpState, PlayerFallState>(PLAYER_FALL);

		// —‰º‘JˆÚæ
		AddChildTransition<PlayerFallState, PlayerFireState>(PLAYER_FIRE);
		AddChildTransition<PlayerFallState, PlayerStepState>(PLAYER_STEP);

		// ”­Ë‘JˆÚæ
		AddChildTransition<PlayerFireState, PlayerFallState>(PLAYER_FALL);

		// “¥‚İ‚Â‚¯‘JˆÚæ
		AddChildTransition<PlayerStepState, PlayerFallState>(PLAYER_FALL);
		AddChildTransition<PlayerStepState, PlayerFireState>(PLAYER_FIRE);

		RegisterStartState<PlayerFloatingEnterState>();
	}

	void PlayerFloatingState::OnEnter()
	{
		_timer = 0.0f;
	}

	void PlayerFloatingState::OnUpdate()
	{

	}

	void PlayerFloatingState::OnExit()
	{


	}
}
