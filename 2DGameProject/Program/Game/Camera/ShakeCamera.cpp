#include "ShakeCamera.h"

namespace Downwell
{
	void ShakeCamera::StartShakeCamera(float shakeRangeX, float shakeRangeY, int shakeFrame, int shakeInterval)
	{

		_shakeRange.Set(shakeRangeX, shakeRangeY);
		_shakeFrame = shakeFrame;
		_shakeInterval = shakeInterval;
		isShake = true;
	}

	void ShakeCamera::StopShakeCamera()
	{
		_shakeRange.Set(0.0f, 0.0f);
		_shakeFrameCounter = 0;
		_shakeFrame = 0;
		_shakeIntervalCounter = 0;
		_shakeInterval = 0;
		isShake = false;
	}

	void ShakeCamera::OnShake()
	{
		if (_shakeFrameCounter >= _shakeFrame)
		{
			StopShakeCamera();
			return;
		}


		if (_shakeIntervalCounter >= _shakeInterval)
		{
			// インターバルの感覚で揺れる
			_shakeSwitch *= -1.0f;
			_transform->position.x += (_shakeRange.x * 0.5f) * _shakeSwitch;
			_transform->position.y += (_shakeRange.y * 0.5f) * _shakeSwitch;
			_shakeIntervalCounter = -1;
		}

		_shakeFrameCounter++;
		_shakeIntervalCounter++;
	}

#pragma region  System Callback Function
	void ShakeCamera::Setup()
	{
		SetOrder(800);

		StopShakeCamera();
	}

	void ShakeCamera::LateUpdate()
	{
		if (isShake == true)
		{
			OnShake();
		}
	}

	void ShakeCamera::End()
	{
	}
#pragma endregion
}