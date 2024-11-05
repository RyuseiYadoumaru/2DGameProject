#pragma  once
#include "CrawlEnemy.h"

namespace Downwell
{
	class CrawlEnemyMovementState : public State<CrawlEnemy>
	{
	public:
		CrawlEnemyMovementState(CrawlEnemy* context, State<CrawlEnemy>* parent);

	public:
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;

	private:
		int _fallFrameCounter = 0;
		int _fallMaxSpeedFrame = 10;
	};
}