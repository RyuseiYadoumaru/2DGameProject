#pragma once
#include "../Include/ObjectInclude.h"
#include "../Include/MathInclude.h"

namespace Downwell
{
	class ShakeCamera : public Script
	{
	public:
		SCRIPT_CLASS;

	public:
		void StartShakeCamera(float shakeRangeX, float shakeRangeY, int shakeFrame, int shakeInterval = 0);
		void StopShakeCamera();

		bool isShake = false;
		int _shakeFrame = 0;
		int _shakeFrameCounter = 0;
		int _shakeInterval = 0;
		int _shakeIntervalCounter = 0;
		Vector2 _shakeRange;

		float _shakeSwitch = 1.0f;

	private:
		void OnShake();

	private:
		void Setup() override;
		void LateUpdate() override;
		void End() override;
	};
}