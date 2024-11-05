#pragma once
#include "../Include/ObjectInclude.h"
#include "../Include/MathInclude.h"

namespace Downwell
{
	class FollowCamera : public Script
	{
	public:
		SCRIPT_CLASS;

	public:
		void SetFollowTransform(Transform* followTrans)		noexcept { _followTrans = followTrans; }
		void ResetFollowTransform() noexcept { _followTrans = nullptr; }
		void SetFollowOffset(const float offsetX, const float offsetY)	noexcept { _followOffset.x = offsetX; _followOffset.y = offsetY; }
		
		void OnEnableRangeY(float min, float max);
		void OnDisableRangeY();

		void SetFollowingDistance(float distance) noexcept { _followingDistance = distance; }
		void SetDelayFrame(int frame) noexcept { _delayFrame = frame; }

		void OnEnableDelay()	noexcept { isDelay = true; }
		void OnDisableDelay()	noexcept { isDelay = false; }

	private:
		const Transform* _followTrans = nullptr;
		Vector2 _followOffset;

		bool enableRangeY = false;
		float _minRangeY = 0.0f;
		float _maxRangeY = 0.0f;

		// ëŒè€ï®Ç∆ÇÃãóó£Ç™ó£ÇÍÇÈÇ∆í«è]ÇäJénÇ∑ÇÈ
		float _followingDistance = 0.0;
		bool isDistant = false;
		float _prePosY = 0.0f;
		int _frame = 0;
		int _delayFrame = 15;
		bool isDelay = false;

		stack<float> _followPosStack;

	private:
		void Following();
		void DelayFollowing();


#pragma region System Callback Functions
	private:
		void Setup() override;
		void LateUpdate() override;
		void End() override;
#pragma endregion

	};
}