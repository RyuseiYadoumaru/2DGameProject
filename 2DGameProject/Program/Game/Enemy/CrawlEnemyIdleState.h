#pragma  once
#include "CrawlEnemy.h"

namespace Downwell
{
	class CrawlEnemyIdleState : public State<CrawlEnemy>
	{
	public:
		CrawlEnemyIdleState(CrawlEnemy* context, State<CrawlEnemy>* parent);

	public:
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;
	};
}