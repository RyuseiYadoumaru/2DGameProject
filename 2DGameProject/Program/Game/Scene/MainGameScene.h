#pragma once
#include "../Include/ObjectInclude.h"

namespace Downwell
{
	class Player;
	class Slide;

	class MainGameScene : public Scene
	{
	public:
		SCENE_CLASS

	private:
		shared_ptr<Player> _player = nullptr;
		shared_ptr<GameObject> _startTransition = nullptr;
		shared_ptr<GameObject> _endTransition = nullptr;

		int _startAnimFrame = 0;
		bool isPlayTransition = false;

		int _endAnimFrame = 0;
		bool isPlayEndTransition = false;

		int _fadeFrame = 20;
		int _fadeWaitFrame = 10;

		int _loadSceneFrame = 0;
		int _waitLoadSceneFrame = 50;

	private:
		void SetupObject() override;
		void BeginPlay() override;
		void Tick() override;
		void EndPlay() override;

	};
}