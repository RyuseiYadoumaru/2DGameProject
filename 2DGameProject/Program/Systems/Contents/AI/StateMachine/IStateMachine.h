#pragma once

namespace myGame::AI
{
	class IStateMachine
	{
	public:
		virtual void OnUpdate() = 0;
	};

	class IState
	{
	public:
		virtual void OnEnter() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnExit() = 0;
	};
}
