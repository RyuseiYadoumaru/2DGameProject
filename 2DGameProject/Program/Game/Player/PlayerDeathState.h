#pragma once
#include "Player.h"

namespace Downwell
{
	class GameOverUI;

	class PlayerDeathState : public State<Player>
	{
	public:
		PlayerDeathState(Player* context, State<Player>* parent);

	public:
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;

	private:
		
		int _frameCounter	 = 0;
		int _showUIWaitFrame = 70;
		
		int _playerFallWaitFrame = 10;
		
		float _deathPlayerShakeRange = 1.0f;
		int _shakeIntervalFrame = 1;
		int _shakeCount = 10;
		int _shakeCounter = 0;
		float _savePlayerDeathPosX = 0.0f;
		float _savePlayerDeathPosY = 0.0f;
		GameOverUI* _gameOverUI = nullptr;
	};
}