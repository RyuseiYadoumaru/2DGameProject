#pragma  once
#include "FloatingEnemy.h"

namespace Downwell
{
	class FloatingEnemyDiscoveryState : public State<FloatingEnemy>
	{
	public:
		FloatingEnemyDiscoveryState(FloatingEnemy* context, State<FloatingEnemy>* parent);

	public:
		virtual void OnEnter() override;
		virtual void OnUpdate() override;
		virtual void OnExit() override;

	private:
		Transform* _targetTrans = nullptr;
	};
}