#include "BreakBlock.h"
#include "../Map/Map2DSponer.h"

namespace Downwell
{
	void BreakBlock::OnHitBullet()
	{
		_ownerSponer->DestroyBlock(_indexX, _indexY);
	}

	void BreakBlock::Setup()
	{
		auto renderer = AddComponent<SpriteRenderer>();
		renderer->SetSprite("Break.png");
		renderer->size.Set(_blockSize, _blockSize);
	}
}