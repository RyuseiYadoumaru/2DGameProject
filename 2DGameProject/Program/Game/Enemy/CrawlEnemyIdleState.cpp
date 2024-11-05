#include "CrawlEnemyIdleState.h"

namespace Downwell
{
	CrawlEnemyIdleState::CrawlEnemyIdleState(CrawlEnemy* context, State<CrawlEnemy>* parent)
		:State<CrawlEnemy>(context, parent)
	{

	}


	void CrawlEnemyIdleState::OnEnter()
	{
	}

	void CrawlEnemyIdleState::OnUpdate()
	{
		// ƒJƒƒ‰‚Ì”ÍˆÍ‚É“ü‚Á‚½‚ç“®‚«o‚·
		bool isAppearCamera = Camera::CheckAppearCamera(GetContext().GetTrans(), 0.0f, 90.0f);
		if (isAppearCamera == true)
		{
			SendTrigger(CRAWL_MOVEMENT);
			return;
		}

		GetContext().GetTrans().moveForce.Set(0.0f, 0.0f);
	}

	void CrawlEnemyIdleState::OnExit()
	{
	}
}