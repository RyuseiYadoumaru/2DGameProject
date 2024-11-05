#pragma once
#include "../Include/MathInclude.h"
#include "../Include/SystemInclude.h"
#include "../Include/ObjectInclude.h"

namespace Downwell
{
	class IPlayerActionEvent
	{
	public:
		virtual void Idle(Transform* outTrans) = 0;
		virtual void Stop(Transform* outTrans) = 0;
		virtual void Movement(Transform* outTrans, float inMaxSpeed, float inMovementPower, int inElapsedFrame) = 0;
		virtual void Rise(Transform* outTrans, float* outCurrentRisePower, float inRisePower, int inRisingFrame, int inElapsedFrame) = 0;
		virtual void Fall(Transform* outTrans, float inMaxSpeed, int inFallMaxSpeedFrame, int inElapsedFrame) = 0;
		virtual void Step(Transform* outTrans, float* outCurrentStepPower, float inStartStepPower, int inStepFrame, int inElapsedFrame) = 0;
	};

	class PlayerActionEvent : public IPlayerActionEvent
	{
	public:
		virtual void Idle(Transform* outTrans);

		virtual void Stop(Transform* outTrans);

		virtual void Movement(Transform* outTrans, float inMaxSpeed, float inMovementPower, int inElapsedFrame) override;

		virtual void Rise(Transform* outTrans, float* outCurrentRisePower, float inRisePower, int inRisingFrame, int inElapsedFrame) override;

		virtual void Fall(Transform* outTrans, float inMaxSpeed, int inFallMaxSpeedFrame, int inElapsedFrame) override;

		virtual void Step(Transform* outTrans, float* outCurrentStepPower, float inStartStepPower, int inStepFrame, int inElapsedFrame);
	};
}