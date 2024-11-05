#pragma once
#include "../Include/ObjectInclude.h"

namespace Downwell
{
	class Map2DSponer;

	class Block : public GameObject
	{
	public:
		GAMEOBJECT_CLASS;

	public:
		virtual void OnHitBullet() { /* empty */ }

	public:
		void SetOwnerSponer(Map2DSponer* sponer) noexcept { _ownerSponer = sponer; }
		void SetIndex(const int x, const int y) noexcept { _indexX = x; _indexY = y; }
		void SetBlockSize(float size) noexcept { _blockSize = size; }
		float GetBlockSize() const noexcept { return _blockSize; }

	protected:
		Map2DSponer* _ownerSponer = nullptr;
		float _blockSize = 0.0f;

		int _indexX = 0;
		int _indexY = 0;

	private:
		void End()
		{
			_ownerSponer = nullptr;
		}
	};
}