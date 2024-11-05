#include "NormalBlock.h"

namespace Downwell
{
	void NormalBlock::Setup()
	{
		auto renderer = AddComponent<SpriteRenderer>();
		
		// ���[�ƉE�[�̃u���b�N��Line�ɂ��Ă��܂�
		string spriteName = "Block2.png";
		if (_indexX == 0) spriteName = "LeftLine.png";
		else if (_indexX == 10) spriteName = "RightLine.png";
		renderer->SetSprite(spriteName);

		renderer->size.Set(_blockSize, _blockSize);
	}
}