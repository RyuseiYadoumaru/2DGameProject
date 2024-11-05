#include "WaveAnimation.h"

namespace Downwell
{
	void WaveAnimation::Start()
	{
		_halfWaveCycleFrame = _waveCycleFrame * 0.5;
	
		// ウェーブの最大値最小値設定
		float maxX = _transform->position.x + _waveRange.x;
		float maxY = _transform->position.y + _waveRange.y;
		_waveMaxPos.Set(maxX, maxY);
		float minX = _transform->position.x - _waveRange.x;
		float minY = _transform->position.y - _waveRange.y;
		_waveMinPos.Set(minX, minY);
	}

	void WaveAnimation::Update()
	{
		// ウェーブサイクルの半分でスイッチする
		if (_frameCounter < 0 || _frameCounter >= _halfWaveCycleFrame) _swich *= -1;

		if (_waveRange.x != 0.0f)
		{
			_transform->position.x = Easing::QuadInOut(static_cast<float>(_frameCounter),
													   static_cast<float>(_halfWaveCycleFrame),
													   _waveMinPos.x, _waveMaxPos.x);
		}

		if (_waveRange.y != 0.0f)
		{
			_transform->position.y = Easing::QuadInOut(static_cast<float>(_frameCounter),
													   static_cast<float>(_halfWaveCycleFrame),
													   _waveMinPos.y, _waveMaxPos.y);
		}

		_frameCounter += _swich;
	}
}