#pragma once
#include "../Include/ObjectInclude.h"

namespace Downwell
{
	class Player;

	class GameClearScene : public Scene
	{
	public:
		SCENE_CLASS

	private:
		void SetupObject() override;
		void BeginPlay() override;
		void Tick() override;
		void EndPlay() override;

	private:
		shared_ptr<Player> _player = nullptr;
		bool canTransitionTitle = false;

		int _frameCounter = 0;
		int _waitTransitionFrame = 95;
	};
}