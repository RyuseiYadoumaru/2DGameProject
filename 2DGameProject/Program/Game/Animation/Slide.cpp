#include "Slide.h"

namespace Downwell
{
	void Slide::OnPlay()
	{
		isPlay = true;
	}

	void Slide::OnPause()
	{
		isPlay = false;
	}

	void Slide::Start()
	{
		_frame = 0;
		_transform->position = _startPos;
	}

	void Slide::Update()
	{
		if (isPlay == false) return;

		if (_frame >= _playFrame)
		{
			_transform->position = _targetPos;
			return;
		}

		_transform->position.x = Easing::Liner(static_cast<float>(_frame),
												 static_cast<float>(_playFrame),
												_startPos.x, _targetPos.x);
		_transform->position.y = Easing::Liner(static_cast<float>(_frame),
												 static_cast<float>(_playFrame),
												_startPos.y, _targetPos.y);
		_frame++;
	}

	void Slide::End()
	{
	}
}