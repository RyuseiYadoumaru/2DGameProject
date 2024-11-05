#pragma once
#include "../Include/ObjectInclude.h"
#include "../Include/MathInclude.h"

namespace Downwell
{
	class WaveAnimation : public Script 
	{
	public:
		SCRIPT_CLASS;

	public:
		void SetWaveRange(float rangeX, float rangeY) noexcept { _waveRange.Set(rangeX, rangeY); }
		void SetWaveCycleFrame(int waveCycle) noexcept { _waveCycleFrame = waveCycle; }

	private:
		Vector2 _waveRange;
		int _frameCounter = 0;
		int _waveCycleFrame = 30;

		int _swich = 1;
		int _halfWaveCycleFrame = 0;
		Vector2 _waveMaxPos;
		Vector2 _waveMinPos;

	private:
		void Start();
		void Update();


	};
}