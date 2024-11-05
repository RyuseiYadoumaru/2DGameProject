#include "PlayerRootState.h"

#include "PlayerActionState.h"
#include "PlayerDeathState.h"

namespace Downwell
{
	PlayerRootState::PlayerRootState(Player* context, State<Player>* parent)
		: State<Player>(context, parent)
	{
		AddChildState<PlayerActionState>();
		AddChildState<PlayerDeathState>();

		AddChildTransition<PlayerActionState, PlayerDeathState>(PLAYER_DEATH);

		RegisterStartState<PlayerActionState>();
	}
	void PlayerRootState::OnEnter()
	{
	}
	void PlayerRootState::OnUpdate()
	{
	}
	void PlayerRootState::OnExit()
	{
	}
}