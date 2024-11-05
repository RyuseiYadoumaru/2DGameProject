#include "PlayerActionEvent.h"

#include "Player.h"
namespace Downwell
{
	void PlayerActionEvent::Idle(Transform* outTrans)
	{
		outTrans->moveForce.x = 0.0f;
	}


	void PlayerActionEvent::Stop(Transform* outTrans)
	{
		outTrans->moveForce.Set(0.0f, 0.0f);
	}


	void PlayerActionEvent::Movement(Transform* outTrans,
									float inMaxSpeed,
									float inMovementPower,
									int inElapsedFrame)
	{
		float moveForceX = inMaxSpeed * inMovementPower;
		outTrans->moveForce.x = moveForceX;
	}


	void PlayerActionEvent::Rise(Transform* outTrans,
								float* outCurrentRisePower,
								float inRisePower,
								int inRisingFrame,
								int inElapsedFrame)
	{
		if (inElapsedFrame >= inRisingFrame) inElapsedFrame = inRisingFrame;
		float riseForce = inRisePower * Easing::SineIn(static_cast<float>(inElapsedFrame), static_cast<float>(inRisingFrame), 1.0f, 0.0f);
		if (riseForce <= 0.0f) riseForce = 0;
		*outCurrentRisePower = riseForce;
		
		// ã‚És‚­‚Ù‚Ç’l‚ª‰º‚ª‚é‚Ì‚Å-1‚ðŠ|‚¯‚Ä‚¢‚Ü‚·
		outTrans->moveForce.y = riseForce * -1.0f;
	}


	void PlayerActionEvent::Fall(Transform* outTrans,
								float inMaxSpeed,
								int inFallMaxSpeedFrame,
								int inElapsedFrame)
	{
		if (inElapsedFrame >= inFallMaxSpeedFrame) inElapsedFrame = inFallMaxSpeedFrame;
		float fallForce = inMaxSpeed * Easing::SineOut(static_cast<float>(inElapsedFrame), static_cast<float>(inFallMaxSpeedFrame), 0.0f, 1.0f);
		outTrans->moveForce.y = fallForce;
	}


	void PlayerActionEvent::Step(Transform* outTrans,
								float* outCurrentStepPower,
								float inStartStepPower,
								int inStepFrame,
								int inElapsedFrame)
	{
		if (inElapsedFrame >= inStepFrame) inElapsedFrame = inStepFrame;
		float riseForce = inStartStepPower * Easing::ExpoIn(static_cast<float>(inElapsedFrame), static_cast<float>(inStepFrame), 1.0f, 0.0f);
		*outCurrentStepPower = riseForce;
		outTrans->moveForce.y = riseForce * -1.0f;
	}
}