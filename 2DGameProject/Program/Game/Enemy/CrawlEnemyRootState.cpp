#include "CrawlEnemyRootState.h"
#include "CrawlEnemyMovementState.h"
#include "CrawlEnemyIdleState.h"

namespace Downwell
{
	CrawlEnemyRootState::CrawlEnemyRootState(CrawlEnemy* context, State<CrawlEnemy>* parent)
		:State<CrawlEnemy>(context, parent)
	{
		AddChildState<CrawlEnemyIdleState>();
		AddChildState<CrawlEnemyMovementState>();

		// ‘Ò‹@
		AddChildTransition<CrawlEnemyIdleState, CrawlEnemyMovementState>(CRAWL_MOVEMENT);
		AddChildTransition<CrawlEnemyMovementState, CrawlEnemyIdleState>(CRAWL_IDLE);

		RegisterStartState<CrawlEnemyIdleState>();
	}


	void CrawlEnemyRootState::OnEnter()
	{
	}

	void CrawlEnemyRootState::OnUpdate()
	{
	}

	void CrawlEnemyRootState::OnExit()
	{
	}
}