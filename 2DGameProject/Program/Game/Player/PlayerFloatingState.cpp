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

		// 開始遷移先
		AddChildTransition<PlayerFloatingEnterState, PlayerFallState>(PLAYER_FALL);
		AddChildTransition<PlayerFloatingEnterState, PlayerJumpState>(PLAYER_JUMP);
		AddChildTransition<PlayerFloatingEnterState, PlayerStepState>(PLAYER_STEP);

		// ジャンプ遷移先
		AddChildTransition<PlayerJumpState, PlayerFallState>(PLAYER_FALL);

		// 落下遷移先
		AddChildTransition<PlayerFallState, PlayerFireState>(PLAYER_FIRE);
		AddChildTransition<PlayerFallState, PlayerStepState>(PLAYER_STEP);

		// 発射遷移先
		AddChildTransition<PlayerFireState, PlayerFallState>(PLAYER_FALL);

		// 踏みつけ遷移先
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
