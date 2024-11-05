#pragma once
#include "Block.h"

namespace Downwell
{
	class BreakBlock : public Block
	{
	public:
		Block::Block;

		void OnHitBullet() override;

	private:
		void Setup() override;

	};
}