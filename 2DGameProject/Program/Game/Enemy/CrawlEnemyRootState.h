#pragma  once
#include "CrawlEnemy.h"

namespace Downwell
{
	class CrawlEnemyRootState : public State<CrawlEnemy>
	{
	public:
		CrawlEnemyRootState(CrawlEnemy* context, State<CrawlEnemy>* parent);

	public:
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;
	};
}