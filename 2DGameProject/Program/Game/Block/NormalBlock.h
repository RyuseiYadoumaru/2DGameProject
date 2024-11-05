#pragma once
#include "Block.h"

namespace Downwell
{
	class NormalBlock : public Block
	{
	public:
		 Block::Block;

	private:
		void Setup() override;

	};
}