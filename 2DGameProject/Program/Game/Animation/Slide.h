#pragma once
#include "../Include/ObjectInclude.h"
#include "../Include/MathInclude.h"

namespace Downwell
{
	class Slide : public Script
	{
	public:
		SCRIPT_CLASS;

	public:
		void OnPlay();
		void OnPause();

	public:
		void SetPlayFrame(int inFrame) noexcept { _playFrame = inFrame; }
		void SetStartPos(float inX, float inY) noexcept { _startPos.Set(inX, inY); }
		void SetTargetPos(float inX, float inY) noexcept { _targetPos.Set(inX, inY); }

	private:
		int _playFrame = 10;
		Vector2 _startPos;
		Vector2 _targetPos;

		int _frame = 0;
		bool isPlay = false;

	private:
		void Start() override;
		void Update() override;
		void End() override;
	};
}