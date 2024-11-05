#pragma once
#include "../Include/ObjectInclude.h"
#include "../Include/AIInclude.h"
#include "../Include/MathInclude.h"

namespace Downwell
{
	class GameOverUI : public GameObject
	{
	public:
		GAMEOBJECT_CLASS;

	public:
		void OnPlay();
		void OnPause();

	private:
		bool isPlay = true;
		TComponentPtr<TextRenderer> _renderer = nullptr;

		float _startPosY = 0.0f;
		float _targetPosY = 0.0f;
		float _riseValue = 30.0f;
		int _riseFrame = 30;
		int _frameCounter = 0;
#pragma region  System Callback Function
	
	public:
		virtual void Setup() override;
		virtual void BeginPlay() override;
		virtual void Tick() override;
		virtual void EndPlay() override;

#pragma endregion
		
	};
}