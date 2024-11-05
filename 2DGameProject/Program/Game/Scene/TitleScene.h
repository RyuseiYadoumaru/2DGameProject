#pragma once
#include "../Include/ObjectInclude.h"

namespace Downwell
{
	class Player;

	class TitleScene : public Scene
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
	};
}